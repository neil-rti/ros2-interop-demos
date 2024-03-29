/*
* (c) Copyright, Real-Time Innovations, 2012.  All rights reserved.
* RTI grants Licensee a license to use, modify, compile, and create derivative
* works of the software solely for use with RTI Connext DDS. Licensee may
* redistribute copies of the software provided that all such copies are subject
* to this license. The software is provided "as is", with no warranty of any
* type, including any warranty for fitness for any purpose. RTI is under no
* obligation to maintain or support the software. RTI shall not be liable for
* any incidental or consequential damages arising out of the use or inability
* to use the software.
*/

/** ================================================================
 * blast_pub_main.cxx
 * Publishes ROS2 PointCloud2 data type at a user-selectable rate.
 * Packets are enumerated and timestamped.
 * 
 * This program take up to 4 arguments(with defaults):
 * pubRate(10Hz), dataSize(8192), topicName(rt/ptc_test), domain(0)
 *
 * Uses data type support code generated by the rtiddsgen command:
 *   rtiddsgen -language C++11 cros2_types.idl
 *
 **/

#include <algorithm>
#include <iostream>
#include <array>
#include "cros2_pointcloud_support.hpp"         // for ROS 2 PointCloud2 (LiDAR) pub/sub

// a few globals for convenience.
int         domain_id = 0;                      // DDS domain number
char        topic_name[255] = "ptc_test_0";     // default topic name
int         pub_rate = 10;                      // publication rate, in samples per second
int         points_total = 0;                   // array size == points_total * 16
int         sample_size_in_bytes = 8192;        // sample size desired
int32_t     tests_to_run = -1;                  // max count of tests to run
uint32_t    tests_run = 0;                      // count of tests run
bool        quit_program = false;
bool        animate_points = false;
const int   bytes_per_point = 16;               // number of bytes per data sample
const int   sample_size_min = 74;               // minimum sample size for PointCloud2.


/** ----------------------------------------------------------------
 * animatePoints()
 * update the position data in the pointcloud
 **/
void animatePoints(float *ptcData)
{
    static bool once = true;
    static struct mvect {
        float   xv;
        float   yv;
        float   zv;
    } *mva = NULL;

    if (once) {
        // create array of random vectors to move points along
        mva = (struct mvect *)malloc(points_total * sizeof(struct mvect));
        for (int i = 0; i < points_total; i++) {
            mva[i].xv = ((static_cast<float>(rand() % 200)) / 500) - 0.2f;
            mva[i].yv = ((static_cast<float>(rand() % 200)) / 500) - 0.2f;
            mva[i].zv = ((static_cast<float>(rand() % 200)) / 500) - 0.2f;
        }
        once = false;
    }
    // move each point according to their random vectors (created above), bounce off of walls (10x10x10)
    for (int i = 0, v=0; i < (points_total*4); i += 4, v++)
    {
        // X
        *(ptcData + i + 0) = (*(ptcData + i + 0) + mva[v].xv);
        if (*(ptcData + i + 0) > 5.0f) {
            *(ptcData + i + 0) = -(*(ptcData + i + 0) - 10.0f);
           mva[v].xv *= -1;
        }
        else if (*(ptcData + i + 0) < -5.0f) {
            *(ptcData + i + 0) = -(*(ptcData + i + 0) + 10.0f);
           mva[v].xv *= -1;
        }

        // Y
        *(ptcData + i + 1) = (*(ptcData + i + 1) +mva[v].yv);
        if (*(ptcData + i + 1) > 5.0f) {
            *(ptcData + i + 1) = -(*(ptcData + i + 1) - 10.0f);
           mva[v].yv *= -1;
        }
        else if (*(ptcData + i + 1) < -5.0f) {
            *(ptcData + i + 1) = -(*(ptcData + i + 1) + 10.0f);
           mva[v].yv *= -1;
        }

        // Z
        *(ptcData + i + 2) = (*(ptcData + i + 2) +mva[v].zv);
        if (*(ptcData + i + 2) > 10.0f) {
            *(ptcData + i + 2) = -(*(ptcData + i + 2) - 20.0f);
           mva[v].zv *= -1;
        }
        else if (*(ptcData + i + 2) < 0.0f) {
            *(ptcData + i + 2) = -(*(ptcData + i + 2));
           mva[v].zv *= -1;
        }
    }
    return;
}


/** ----------------------------------------------------------------
 * participant_main()
 **/
void participant_main(void)
{
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


    uint32_t nsSleep = ((uint32_t)1000000000) / pub_rate;
    tests_run = (uint32_t)tests_to_run;
    uint32_t tests_per_sec = 0;
    timespec tStart, tLap;
    tstamp_get(&tStart);
    // main loop --------------------------------------------------------------
    fprintf(stdout, "READY\n");
    for (uint32_t wcount = 0; !quit_program; wcount++) {

        // send a sample, with the lowest 22 bits of (float)data[0] holding the seq number
        // (note that the PointCloud2.header.timestamp is updated by the .publish() call).
        uint32_t tdZero = *(uint32_t *)(pubArray);
        tdZero &= 0xffc00000;
        tdZero |= (wcount & 0x3fffff);
        *(uint32_t *)(pubArray) = tdZero;

        //printf("Sending: %u\n", testIdx);
        myLidarPub.publish();

        // finished testing?
        if ((--tests_run) == 0) {
            quit_program = true;
        }

        // animate the data points?
        if (animate_points) {
            animatePoints(ptcData);
        }

        // calc the actual pubrate, once per second
        tests_per_sec++;
        tstamp_get(&tLap);
        uint64_t tDiff = ((tLap.tv_sec - tStart.tv_sec) * 1000000000) + (tLap.tv_nsec - tStart.tv_nsec);
        if (tDiff > 1000000000) {
            float sps = (((float)tests_per_sec) * 1000000000) / tDiff;
            uint32_t bps = ((points_total * bytes_per_point) + sample_size_min);
            fprintf(stdout, "PubRate: %4.1f * %u = %u bytes/sec, ", sps, bps, (uint32_t)((float)bps*sps));
            
            // adjust sleep time to improve accuracy in pubrate
            float rate_err = sps / (float)pub_rate;
            nsSleep = (float)nsSleep * rate_err;
            if (nsSleep < 30000) nsSleep = 30000;
            fprintf(stdout, " loop delay: %u\n", nsSleep);

            tStart = tLap;
            tests_per_sec = 0;
        }

        rti::util::sleep(dds::core::Duration(0, nsSleep));

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

