/** -------------------------
 * pointcam.cpp
 * Use OpenCV + Connext to convert video to PointCloud2
 **/
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <array>
#include "cros2_pointcloud_support.hpp"         // for ROS 2 PointCloud2 (LiDAR) pub/sub
#include "pic_frame_motion_depth.hpp"

using namespace cv;
using namespace std;

// a few globals for convenience.
int         domain_id = 0;                      // DDS domain number
char        topic_name[255] = "ptc_test_0";     // default topic name
int         pub_rate = 10;                      // publication rate, in samples per second
int         points_total = 0;                   // array size == points_total * 16
int         sample_size_in_bytes = 15555;        // sample size desired
int32_t     tests_to_run = -1;                  // max count of tests to run
uint32_t    tests_run = 0;                      // count of tests run
bool        quit_program = false;
bool        animate_points = false;
const int   bytes_per_point = 16;               // number of bytes per data sample
const int   sample_size_min = 74;               // minimum sample size for PointCloud2.


/** ----------------------------------------------------------------
 * participant_main()
 **/
void participant_main(void)
{
    //Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        cin.get(); //wait for any key press
        return;  // FIXME: change to THROW
    }
  
    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    string window_name = "My Camera Feed";
    namedWindow(window_name); //create a window called "My Camera Feed"
   
    // Create a DomainParticipant with default Qos
    dds::domain::DomainParticipant participant(domain_id);

    // Instantiate an exporter of PointCloud2(LiDAR) and init the sample
    cros2pointcloud myLidarPub(std::string(topic_name), ((uint32_t)1 << CROS2_PUB_ON), participant);
    myLidarPub.pub_sample_config_fields(PTCLOUD2_FMT_XYZ_RGB8_FLOAT32);
    myLidarPub.pub_sample_isdense_set(true);
    myLidarPub.pub_sample_isbigendian_set(false);
    myLidarPub.pub_sample_header_frameid_set("map");
    myLidarPub.pub_sample_size_xy_set(points_total, 1);
    float *ptcData = myLidarPub.get_send_data_buffer();
    uint8_t *pubArray = (uint8_t *)ptcData;
    for (int i = 0; i < (points_total*4); i+=4)
    {
        *(ptcData + i + 0) = static_cast<float>(((rand() % 1000) / 100.0f) - 5.0f);  // X: -5 to 5
        *(ptcData + i + 1) = static_cast<float>(((rand() % 1000) / 100.0f) - 5.0f);  // Y: -5 to 5
        *(ptcData + i + 2) = static_cast<float>((rand() % 1000) / 100.0f);  // Z:  0 to 10
        // RGB
        *(ptcData + i + 3) = static_cast<float>(
            (((rand() % 255) | 0x25) * 65536) +
            (((rand() % 255) | 0x25) *   256) +
            (( rand() % 255) | 0x25));
    }

    picFrameMotion myFrame(640, 480);

    uint32_t nsSleep = ((uint32_t)1000000000) / pub_rate;
    tests_run = (uint32_t)tests_to_run;
    uint32_t tests_per_sec = 0;
    uint32_t lfsr = 0x8675309;
    timespec tStart, tLap;
    tstamp_get(&tStart);
    // main loop --------------------------------------------------------------
    fprintf(stdout, "READY\n");
    for (uint32_t wcount = 0; !quit_program; wcount++) {

        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get(); //Wait for any key press
            break;
        }

        myFrame.FrameProcess(frame);

        // collect pseudorandom pixels from the image, convert to PointCloud2
        ptcData = myLidarPub.get_send_data_buffer();
        for (int i = 0; i < (points_total * 4); i += 4)
        {
            // prng select a pixel row/col
            int pix_x = lfsr % frame.cols;
            int pix_y = (lfsr >> 16) % frame.rows;
            lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xD0000001u);
            float ptc_x = static_cast<float>((((float)(pix_x * 10)) / (frame.cols)) - 5.0f);
            float ptc_z = static_cast<float>((((float)(pix_y * -10)) / (frame.rows)) + 10.0f);

            // Use pixel --> PointCloud2 values: pixX-->ptcX, pixY-->ptcZ, pixIntensity-->ptcY, pixRGB-->ptcRGB
            *(ptcData + i + 0) = ptc_x;         // X: -5 to 5
            *(ptcData + i + 2) = ptc_z;         // Z:  0 to 10


#if 1
            // for the ptc_y axis: maintain an average intensity map: whatever CHANGES gets moved forward
            // NOTE also: this averaging approach can help to guide where to take random samples (more samples in moving areas)
            *(ptcData + i + 1) = myFrame.getPointDepth(pix_x, pix_y);       // Y axis
#else
            // pix intensity (max: 255*3=765) to set ptc_y; use delta between colors to set Y
            uint32_t pix_intensity = abs(frame.at<Vec3b>(pix_y, pix_x)[0] - frame.at<Vec3b>(pix_y, pix_x)[1])
                + abs(frame.at<Vec3b>(pix_y, pix_x)[1] - frame.at<Vec3b>(pix_y, pix_x)[2])
                + abs(frame.at<Vec3b>(pix_y, pix_x)[2] - frame.at<Vec3b>(pix_y, pix_x)[0]);
            *(ptcData + i + 1) = static_cast<float>((((float)pix_intensity) / -50.0f) + 5.0f);               // Y: -5 to n
#endif
            // BGR point color (Ptc quad is: 0:R:G:B)
            uint32_t pcColor = (((((uint32_t)frame.at<Vec3b>(pix_y, pix_x)[2])) * 65536) +
                ((((uint32_t)frame.at<Vec3b>(pix_y, pix_x)[1])) * 256) +
                (((uint32_t)frame.at<Vec3b>(pix_y, pix_x)[0])));
            * (ptcData + i + 3) = *reinterpret_cast<float*>(&pcColor);
        }

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop 
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }

        //printf("Sending: %u\n", testIdx);
        myLidarPub.publish();

        //show the frame in the created window
        imshow(window_name, frame);

    }
}

/** ---------------------------------------------------------------------------
 * errPrintUsage()
 *
 **/
void errPrintUsage(char *progname)
{
    fprintf(stdout, "%s options:\n", progname);
    fprintf(stdout, "-r <perSec>      Rate of publication, in samples per second (%d)\n", pub_rate);
    fprintf(stdout, "-n <name>        Name of data topic (%s)\n", topic_name);
    fprintf(stdout, "-d <0-240>       DDS Domain Number (%d)\n", domain_id);
    fprintf(stdout, "-s <0-...>       Size (approx) of sample, in bytes(%d)\n", sample_size_in_bytes);
    fprintf(stdout, "-t <1-...>       Total number of tests to run (%d)\n", tests_to_run);
    fprintf(stdout, "-a               Animate the data points\n");
    fprintf(stdout, "-h               Print this message and exit\n\n");
    return;
}

/** ----------------------------------------------------------------
 * main()
 **/
int main(int argc, char *argv[])
{
    // -------------------------------------------------------------------------
    // parse the args
    int domainNumberIsArg = 0;
    int sampleSizeIsArg = 0;
    int topicNameIsArg = 0;
    int testIterationsIsArg = 0;
    int pubRateIsArg = 0;

    int i = -1;
    int iarg = 1;
    while (iarg < argc)
    {
        if (argv[iarg][0] == '-')
        {
            if ((int)strlen(argv[iarg]) > 1)
            {
                switch (argv[iarg][1])
                {
                case 'a':       // Animate the data points
                    animate_points = true;
                    break;

                case 'd':       // DDS Domain Number (number is the next arg)
                    domainNumberIsArg = iarg + 1;
                    break;

                case 'h':       // print help and exit
                    errPrintUsage(argv[0]);
                    return(-1);

                case 'n':       // DDS topic name to publish
                    topicNameIsArg = iarg + 1;
                    break;

                case 'r':       // publication rate
                    pubRateIsArg = iarg + 1;
                    break;

                case 's':       // Data sample size in bytes (number is next arg)
                    sampleSizeIsArg = iarg + 1;
                    break;

                case 't':       // Total number of tests to run
                    testIterationsIsArg = iarg + 1;
                    break;

                default:
                    fprintf(stderr, "Invalid option: \"%c\" - Ignored\n", argv[iarg][2]);
                    break;
                }
            }
            iarg++;
        }
        else
        {
            if (sampleSizeIsArg == iarg) {
                sample_size_in_bytes = atoi(argv[iarg]);
            }
            else if (pubRateIsArg == iarg) {
                pub_rate = atoi(argv[iarg]);
            }
            else if (domainNumberIsArg == iarg) {
                domain_id = atoi(argv[iarg]);
            }
            else if (topicNameIsArg == iarg) {
                strcpy(topic_name, argv[iarg]);
            }
            else if (testIterationsIsArg == iarg) {
                tests_to_run = atoi(argv[iarg]);
            }
            iarg++;
        }
    }

    // minimum size is 1 point
    if (sample_size_in_bytes < (sample_size_min + bytes_per_point)) {
        fprintf(stderr, "Setting to minimum sample size (total): %d bytes with 1 point\n", sample_size_min + bytes_per_point);
        sample_size_in_bytes = (sample_size_min + bytes_per_point);
    }
    points_total = ((sample_size_in_bytes - sample_size_min) / bytes_per_point);
    fprintf(stdout, "PointCloud2 samples will contain (%d) %d-byte points + %d bytes = %d bytes\n", 
        points_total, bytes_per_point, sample_size_min, (points_total * bytes_per_point) + sample_size_min);

    // To turn on additional logging, include <rti/config/Logger.hpp> and
    // uncomment the following line:
    // rti::config::Logger::instance().verbosity(rti::config::Verbosity::STATUS_ALL);

    try {
        participant_main();
    }
    catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in participant_main(): " << ex.what() << std::endl;
        return -1;
    }

    // RTI Connext provides a finalize_participant_factory() method
    // if you want to release memory used by the participant factory singleton.
    // Uncomment the following line to release the singleton:
    //
    //dds::domain::DomainParticipant::finalize_participant_factory();

    return 0;
}

