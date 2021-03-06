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
 * wrap_bench_main.cxx
 * Publishes ROS2 PointCloud2 data type to a test application
 *  (ROS2 or DDS), and awaits a converted-to-PointCloud2 topic receive.
 * Takes timing measurements to determine latency.
 * Uses data type support code generated by the rtiddsgen command:
 *   rtiddsgen -language C++11 cros2_types.idl
 *
 **/

#include <algorithm>
#include <iostream>
#include <array>
#ifdef WIN32
#include <conio.h>                              // for kbhit()
#endif
#include "cros2_pointcloud_support.hpp"         // for ROS 2 PointCloud2 (LiDAR) pub/sub

// a few globals for convenience.
int         domain_id = 0;              // DDS domain number
uint32_t    *bins;                      // array of 1uS wide histogram bins (allocated in participant_main)
int         bins_total = 40000;         // number of bins to allocate
uint32_t    bin_width = 50;             // width (in microseconds) of the histogram bins when printing CSV file
int         points_total = 512;         // array size == points_total * 16
uint32_t    tests_to_run = 32768;       // max count of tests to run
uint32_t    tests_run = 0;              // count of tests run
int         subscriber_count = 1;       // number of subscribers to create
uint32_t    waitset_delay = 6000000;    // time to spend in waitset
bool        interactive_mode = false;
bool        publish_on = false;
bool        quit_program = false;
bool        sub_count_changed = false;
bool        animate_points = false;
std::array<uint64_t, 256> roster;


/** ----------------------------------------------------------------
 * statsPrinter()
 **/
void statsPrinter(void)
{
    // find min/mean/max and count
    uint32_t tMin = 0;
    uint32_t tMax = 0;
    uint32_t tCnt = 0;
    uint64_t tSum = 0;
    for (int i = 0; i < bins_total; i++) {
        tSum += bins[i] * ((uint64_t)i);
        if (bins[i]) {
            if (tMin == 0) {
                tMin = i;
            }
            tMax = i;
            tCnt += bins[i];
        }
    }
    double tMean = (double)tSum / tCnt;
    // find standard deviation
    double tVar = 0;
    for (int i = 0; i < bins_total; i++) {
        if (bins[i]) {
            tVar += (pow(i - tMean, 2) * bins[i]);
        }
    }
    double stdDev = sqrt(tVar / tCnt);
    fprintf(stdout, "tMin, %u, tMean, %5.3f, tMax, %u, stdDev, %5.3f, tCnt, %u\n", tMin, tMean, tMax, stdDev, tCnt);

}

/** ----------------------------------------------------------------
 * binPrinter()
 * Print (to stdout) the counts in the bins, at the selected bin width
 **/
void binPrinter(void)
{
    // first: find the last nonzero value; suppress prints after that bin
    int last_occupied_bin = bins_total - 1;
    while ((bins[last_occupied_bin] == 0) && (last_occupied_bin)) {
        last_occupied_bin--;
    }

    // print out the bins to the nearest binRes batch
    uint32_t binSum = 0;
    uint32_t binI = 0;
    fprintf(stdout, "TestsRun, %u, BinSize, %u, ----------------------------------------\n", tests_run, bin_width);
    fprintf(stdout, "uSecs, testCount\n");
    for (int j = 0; j <= last_occupied_bin; j++) {
        if (bins[j]) {
            binSum += bins[j];
        }
        binI++;
        if (binI >= bin_width) {
            fprintf(stdout, "%5d, %6u\n", j - bin_width + 1, binSum);
            binI = 0;
            binSum = 0;
        }
    }
    fprintf(stdout, "\n");

    return;
}

/** ----------------------------------------------------------------
 * writeCsvFile()
 * Open and write a csv file with the bin counts, stats, etc.
 **/
void writeCsvFile(void)
{
    // print out the bins to the nearest binRes batch
    uint32_t binSum = 0;
    uint32_t binI = 0;
    fprintf(stdout, "TestsRun, %u, BinSize, %u, ----------------------------------------\n", tests_run, bin_width);
    fprintf(stdout, "uSecs, testCount\n");
    for (int j = 0; j < bins_total; j++) {
        if (bins[j]) {
            binSum += bins[j];
        }
        binI++;
        if (binI >= bin_width) {
            fprintf(stdout, "%5d, %6u\n", j - bin_width + 1, binSum);
            binI = 0;
            binSum = 0;
        }
    }
    fprintf(stdout, "\n");

    return;
}


/** ----------------------------------------------------------------
 * binClear()
 * Clear all bin counts to 0, all stats and counts.
 **/
void binClear(void)
{
    for (int i = 0; i < bins_total; i++) {
        bins[i] = 0;
    }
    tests_run = 0;
    return;
}


/** ----------------------------------------------------------------
 * showSettings()
 * Show the current test settings
**/
void showSettings(void)
{
    fprintf(stdout, "DDS Domain %d, Pub(p): %s, Subs(+/-): %d, wsDelay(d): %1.6f, dataSize(a): %u points = %u bytes\n", 
        domain_id, publish_on?"ON":"OFF", subscriber_count, ((float)waitset_delay / 1000000000), points_total, points_total*16);
    fprintf(stdout, "1uS bins[%u], binSize(b): %u uS, testToRun(c): %u, testsRun(r): %u\n", bins_total, bin_width, tests_to_run, tests_run);
    return;
}

bool buildKeyNumber(int keycode, uint32_t *val)
{
    if ((keycode >= '0') && (keycode <= '9')) {
        *val = *val * 10;
        *val = *val + (keycode - '0');
        fprintf(stdout, "%c", keycode);
        return true;
    }
    else {
        return false;
    }
}


void printInteractiveHelp(void) {
    fprintf(stdout, "'?' : show current settings\n");
    fprintf(stdout, "'+' : add a subscriber\n");
    fprintf(stdout, "'-' : remove a subscriber\n");
    fprintf(stdout, "'=' : show stats\n");
    fprintf(stdout, "'a' : ARRAY size (in 16-byte points) to be published\n");
    fprintf(stdout, "'b' : BIN size (in microseconds) of histogram result\n");
    fprintf(stdout, "'c' : COUNT of tests to run (then stop but do not exit)\n");
    fprintf(stdout, "'d' : DELAY between publications\n");
    fprintf(stdout, "'g' : GO animate pointcloud (between tests)\n");
    fprintf(stdout, "'h' : HELP\n");
    fprintf(stdout, "'m' : merge test results\n");
    fprintf(stdout, "'p' : start/stop publishing\n");
    fprintf(stdout, "'q' : change QoS\n");
    fprintf(stdout, "'r' : RESET histogram bins to 0\n");
    fprintf(stdout, "'s' : SHOW (print) the CSV data\n");
    fprintf(stdout, "'w' : WRITE data to CSV file\n");
    fprintf(stdout, "'x' : EXIT\n");
    return;
}


/** ----------------------------------------------------------------
 * keyProcessor()
 * Process the keypress & set globals
 **/
void keyProcessor(int keycode)
{
    static enum kcMode {
        KC_OPEN, KC_ARRAYSIZE, KC_SETCOUNT, KC_SETDELAY, KC_QOSCHANGE,
        KC_BINSIZE, KC_HISTORESET, KC_WRITEFILE, KC_EXIT
    } km = KC_OPEN;
    static uint32_t tmpVal = 0;
    
    //fprintf(stdout, "Keycode: %3d: ", keycode);
    int c = tolower(keycode);
    switch (km) {
    case KC_OPEN:
        switch (c) {
        case '+':       // add a subscriber
            fprintf(stdout, "add a subscriber\n");
            subscriber_count++;
            sub_count_changed = true;
            break;
        case '-':       // remove a subscriber
            fprintf(stdout, "remove a subscriber\n");
            if (subscriber_count > 0) {
                subscriber_count--;
                sub_count_changed = true;
            }
            break;
        case '=':       // show stats
            statsPrinter();
            break;
        case '?':       // show settings
            showSettings();
            break;
        case 'a':       // array size (published)
            fprintf(stdout, "array size\n");
            tmpVal = 0;
            km = KC_ARRAYSIZE;
            break;
        case 'b':       // bin size of CSV histogram
            fprintf(stdout, "bin size\n");
            tmpVal = 0;
            km = KC_BINSIZE;
            break;
        case 'c':       // set a count to stop testing (but do not exit)
            fprintf(stdout, "set count\n");
            tmpVal = 0;
            km = KC_SETCOUNT;
            break;
        case 'd':       // delay between publications
            fprintf(stdout, "set delay\n");
            tmpVal = 0;
            km = KC_SETDELAY;
            break;
        case 'g':       // Go animate points (between tests)
            fprintf(stdout, "Go (toggle) animate pointcloud (%d --> %d)\n", animate_points, !animate_points);
            animate_points = !animate_points;
            break;
        case 'h':       // help
            printInteractiveHelp();
            break;
        case 'm':       // merge test results 
            fprintf(stdout, "merge tests\n");
            break;
        case 'p':       // start/stop publishing
            fprintf(stdout, "start/stop pub (%d --> %d)\n", publish_on, !publish_on);
            publish_on = !publish_on;
            break;
        case 'q':       // change QoS
            fprintf(stdout, "change QoS\n");
            km = KC_QOSCHANGE;
            break;
        case 'r':       // reset histogram bins to 0
            fprintf(stdout, "Press R to reset stats & histogram counts\n");
            km = KC_HISTORESET;
            break;
        case 's':       // SHOW (print) data 
            fprintf(stdout, "SHOW data that would be printed to file\n");
            statsPrinter();
            binPrinter();
            break;
        case 'w':       // write data to CSV file
            fprintf(stdout, "write data to CSV file\n");
            km = KC_WRITEFILE;
            break;
        case 'x':       // exit
            fprintf(stdout, "exit\n");
            fprintf(stdout, "Press ENTER to exit program\n");
            km = KC_EXIT;
            break;
        default:
            fprintf(stdout, "no cmd -----------\n");
            km = KC_OPEN;
            break;
        };
        break;

    case KC_ARRAYSIZE:
        km = KC_OPEN;
        break;

    case KC_BINSIZE:
        if (!(buildKeyNumber(c, &tmpVal))) {
            fprintf(stdout, "BinSize set to: %u uSecs\n", tmpVal);
            bin_width = tmpVal;
            km = KC_OPEN;
        }
        break;

    case KC_SETCOUNT:
        if (!(buildKeyNumber(c, &tmpVal))) {
            fprintf(stdout, "Value is: %u\n", tmpVal);
            tests_to_run = tmpVal;
            km = KC_OPEN;
        }
        break;

    case KC_SETDELAY:
        if (!(buildKeyNumber(c, &tmpVal))) {
            fprintf(stdout, "Value is: %u\n", tmpVal);
            waitset_delay = tmpVal;
            km = KC_OPEN;
        }
        break;

    case KC_QOSCHANGE:
        km = KC_OPEN;
        break;
    case KC_HISTORESET:
        if (c == 'r') {
            binClear();
            fprintf(stdout, "bins cleared to 0\n");
        }
        km = KC_OPEN;
        break;
    case KC_WRITEFILE:
        km = KC_OPEN;
        break;
    case KC_EXIT:
        quit_program = true;
        km = KC_OPEN;
        break;
    default:
        km = KC_OPEN;
        break;

    }
    return;
}

/** ----------------------------------------------------------------
 * animatePoints()
 * update the position data in the pointcloud
 **/
void animatePoints(float *ptcData, int point_count)
{
    static bool once = true;
    static struct mvect {
        float   xv;
        float   yv;
        float   zv;
    } *mva = NULL;

    if (once) {
        // create array of random vectors to move points along
        mva = (struct mvect *)malloc(point_count * sizeof(struct mvect));
        for (int i = 0; i < point_count; i++) {
            mva[i].xv = ((static_cast<float>(rand() % 400)) / 2000) - 0.1f;
            mva[i].yv = ((static_cast<float>(rand() % 400)) / 2000) - 0.1f;
            mva[i].zv = ((static_cast<float>(rand() % 400)) / 2000) - 0.1f;
        }
        once = false;
    }
    // move each point according to their random vectors (created above), bounce off of walls (10x10x10)
    for (int i = 0; i < point_count; i++)
    {
        float *pBase = (ptcData + (i*4));
        // X
        *(pBase + 0) = (*(pBase + 0) + mva[i].xv);
        if (*(pBase + 0) > 5.0f) {
            *(pBase + 0) = -(*(pBase + 0) - 10.0f);
            mva[i].xv *= -1;
        }
        else if (*(pBase + 0) < -5.0f) {
            *(pBase + 0) = -(*(pBase + 0) + 10.0f);
            mva[i].xv *= -1;
        }

        // Y
        *(pBase + 1) = (*(pBase + 1) + mva[i].yv);
        if (*(pBase + 1) > 5.0f) {
            *(pBase + 1) = -(*(pBase + 1) - 10.0f);
            mva[i].yv *= -1;
        }
        else if (*(pBase + 1) < -5.0f) {
            *(pBase + 1) = -(*(pBase + 1) + 10.0f);
            mva[i].yv *= -1;
        }

        // Z
        *(pBase + 2) = (*(pBase + 2) + mva[i].zv);
        if (*(pBase + 2) > 10.0f) {
            *(pBase + 2) = -(*(pBase + 2) - 20.0f);
            mva[i].zv *= -1;
        }
        else if (*(pBase + 2) < 0.0f) {
            *(pBase + 2) = -(*(pBase + 2));
            mva[i].zv *= -1;
        }
    }
    return;
}


/** ----------------------------------------------------------------
 * ptcloud2_benchRcv()
 * Received 'PointCloud2' data handler.
 * Will timestamp the samples on reception & add to bins.
 **/
int ptcloud2_benchRcv(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_ >& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<sensor_msgs::msg::dds_::PointCloud2_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            timespec rcv_tstamp;
            tstamp_get(&rcv_tstamp);
            //printf("Rcv: %u\n", sample.data().data().at(0));
            count++;

            uint64_t tSub = (rcv_tstamp.tv_sec * 1000000000) + rcv_tstamp.tv_nsec;
            uint8_t sNum = sample.data().data().at(0);

            //fprintf(stdout, "rcv[%u] tSub: %llu, tPub: %llu, tDelta: %llu, total: %u, dropped: %u\n", sNum, tSub, roster[sNum], (tSub - roster[sNum]), tests_run, dropped_samples);

            if (roster[sNum]) {
                uint64_t tBin = (tSub - roster[sNum]) / 1000;
                if (tBin < (bins_total - 1)) {
                    bins[tBin]++;
                }
                else {
                    // topmost bin is for all numbers over the limit.
                    bins[bins_total - 1]++;
                }
            }
            else {
                fprintf(stdout, " dropped sample?\n");
            }

        }
    }
    //std::cout <<  std::endl;
    //if (count > 1)  printf("Count: %u new, total: %u\n", count, tests_run);
    tests_run += count;
    return count;
}


/** ----------------------------------------------------------------
 * participant_main()
 **/
void participant_main(void)
{
    // Create a DomainParticipant with default Qos
    dds::domain::DomainParticipant participant(domain_id);


    // Instantiate an exporter of PointCloud2(LiDAR) and init the sample
    cros2pointcloud myLidarPub(std::string("cloud_call"), ((uint32_t)1 << CROS2_PUB_ON), participant);
    myLidarPub.pub_sample_config_fields(PTCLOUD2_FMT_XYZ_RGB8_FLOAT32);
    myLidarPub.pub_sample_isdense_set(true);
    myLidarPub.pub_sample_isbigendian_set(false);
    myLidarPub.pub_sample_header_frameid_set("map");
    myLidarPub.pub_sample_size_xy_set(points_total, 1);
    float *ptcData = myLidarPub.get_send_data_buffer();
    uint8_t *pubArray = (uint8_t *)ptcData;
    for(int i=0 ; i<points_total ; i++)
    {
        float *pBase = (ptcData + (i*4));
        *(pBase + 0) = static_cast<float>(((rand() % 1000) / 100.0f) - 5.0f);  // X: -5 to 5
        *(pBase + 1) = static_cast<float>(((rand() % 1000) / 100.0f) - 5.0f);  // Y: -5 to 5
        *(pBase + 2) = static_cast<float>((rand() % 1000) / 100.0f);           // Z:  0 to 10
        *(pBase + 3) = static_cast<float>(
            (((rand() % 255) | 0x25) * 65536) +
            (((rand() % 255) | 0x25) *   256) +
            (( rand() % 255) | 0x25));                          // RGB color of the point
    }

    // Instantiate a subscriber of PointCloud2(LiDAR) and init the sample
    int(*rcv_handler)(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_>);
    rcv_handler = (int(*)(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_>))ptcloud2_benchRcv;
    cros2pointcloud myLidarSub(std::string("cloud_echo"), ((uint32_t)1 << CROS2_SUB_ON), participant, rcv_handler);
    //myLidarSub.pub_sample_size_xy_set(points_total, 1);

    // allocate an array for histogram of results, each representing a 1uS bin.
    bins = (uint32_t *)calloc(bins_total, sizeof(uint32_t));
    timespec ts_pub;
    uint32_t dropped_samples = 0;
    int pub_delay = 0;
    uint32_t tests_ref = tests_run;

    // main loop --------------------------------------------------------------
    fprintf(stdout, "READY\n");
    for (int wcount = 0; !quit_program; wcount++) {
        // check for keypress
#ifdef WIN32
        if (interactive_mode) {
            if (_kbhit()) {
                keyProcessor(_getch());
            }
        }
#endif
     
        // if testing is enabled
        if (publish_on) {
            // send a sample
            uint8_t testIdx = static_cast<uint8_t>(wcount);
            *(pubArray) = testIdx;
            tstamp_get(&ts_pub);
            uint64_t tPub = (ts_pub.tv_sec * 1000000000) + ts_pub.tv_nsec;
            roster[testIdx] = tPub;
            //printf("Sending: %u\n", testIdx);
            myLidarPub.publish();

            // loop to do fast waitset polling
            int poll_max = 1000;
            while (poll_max) {
                // check for data received
                myLidarSub.datarcv_waitset(0, 30000);
                if(tests_ref == tests_run) {
                    poll_max--; // no new data
                }
                else {
                    tests_ref = tests_run;
                    break;
                }
            }
            // show progress
            if (!(tests_run & 0xfff))
            {
                fprintf(stderr, ".");
            }
            if (tests_run >= tests_to_run) {
                fprintf(stdout, "\n");
                statsPrinter();
                binPrinter();
                return;
            }

            // if timing out before getting a packet returned, sleep for a bit
            if (poll_max == 0) {
                fprintf(stdout, "packets?  not here\n");
                rti::util::sleep(dds::core::Duration(1, 3000000));
            }
        }
        // animate the data points?
        if (animate_points) {
            animatePoints(ptcData, points_total);
        }
        // rti::util::sleep(dds::core::Duration(0, 300000));
    }
}

/** ---------------------------------------------------------------------------
 * errPrintUsage()
 *
 **/
void errPrintUsage(char *progname)
{
    fprintf(stdout, "%s options:\n", progname);
    fprintf(stdout, "-d <0-240>       DDS Domain Number (%d)\n", domain_id);
    fprintf(stdout, "-t <1-...>       Total number of tests to run (%u)\n", tests_to_run);
    fprintf(stdout, "-a <0-...>       Data array payload size in points(16 bytes per)(%d)\n", points_total);
    fprintf(stdout, "-b <1-1000>      Histogram bin width in microseconds (%d)\n", bin_width);
    fprintf(stdout, "-i               Interactive mode.  Start/stop/print/reset by keypress\n");
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
    int arraySizeIsArg = 0;
    int binWidthIsArg = 0;
    int testIterationsIsArg = 0;

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
                case 'a':       // Data array payload size in bytes (number is next arg)
                    arraySizeIsArg = iarg + 1;
                    break;

                case 'b':       // Histogram bin width in microseconds (number is next arg)
                    binWidthIsArg = iarg + 1;
                    break;

                case 'd':       // DDS Domain Number (number is the next arg)
                    domainNumberIsArg = iarg + 1;
                    break;

                case 'h':       // print help and exit
                    errPrintUsage(argv[0]);
                    return(-1);

                case 'i':       // INTERACTIVE mode
                    interactive_mode = true;
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
            if (arraySizeIsArg == iarg) {
                points_total = atoi(argv[iarg]);
            }
            else if (binWidthIsArg == iarg) {
                bin_width = atoi(argv[iarg]);
            }
            else if (domainNumberIsArg == iarg) {
                domain_id = atoi(argv[iarg]);
            }
            else if (testIterationsIsArg == iarg) {
                tests_to_run = atoi(argv[iarg]);
            }
            iarg++;
        }
    }

    fprintf(stdout, "Starting in ");
    if (interactive_mode) {
        fprintf(stdout, "INTERACTIVE mode, press H for help menu\n");
    }
    else {
        fprintf(stdout, "AUTOMATIC mode: run %u tests with array of %u points (%u bytes), binsize: %u uS\n", 
            tests_to_run, points_total, points_total * 16, bin_width);
        publish_on = true;
    }

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

