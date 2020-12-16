/** ==================================================================
 * FILE: shapesdemo_support.cxx
 * Class for interfacing a native Connext DDS application with the 
 *  ShapeTypeExtended data type.
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 <typedef-file.idl>
**/
#include "shapesdemo_support.hpp"

/*ci
 * \brief shapesdemo class constructor
 *
 * \details
 * Instantiate a ShapeTypeExtended publisher 
 * and/or subscriber with supporting writer, reader, topic, etc.
 *
 * \param[in]    shapeName    Name of the DDS topic (Square, Circle, Triangle)
 * \param[in]    opt_en       bitfield of options (pub, sub) to enable
 * \param[in]    participant  DDS participant, already created
 * \param[in]    *rcv_fptr    Optional pointer to external received data processor
 */
shapesdemo::shapesdemo(const std::string shapeName, uint32_t opt_en, dds::domain::DomainParticipant participant,
    int(*rcv_fptr)(dds::sub::DataReader<ShapeTypeExtended>)) :
    pub_topic(dds::core::null), pub_sample(),
    data_wr(dds::core::null), 
    sub_topic(dds::core::null), data_rd(dds::core::null),
    waitset()
{
    if (opt_en & (1 << SHAPESDEMO_PUB_ON)) {
        // create topics
        pub_topic = dds::topic::Topic<ShapeTypeExtended>(participant, shapeName);

        // DataWriter
        data_wr = dds::pub::DataWriter<ShapeTypeExtended>(dds::pub::Publisher(participant), pub_topic);
    }

    if (opt_en & (1 << SHAPESDEMO_SUB_ON)) {
        sub_topic = dds::topic::Topic<ShapeTypeExtended>(participant, shapeName);
        // DataReader, ReadCondition, WaitSet
        data_rd = dds::sub::DataReader<ShapeTypeExtended>(dds::sub::Subscriber(participant), sub_topic);
        dds::sub::cond::ReadCondition data_readCond(
            data_rd, dds::sub::status::DataState::any(),
            [rcv_fptr, this](/* dds::core::cond::Condition condition */)
        {
            if (rcv_fptr == NULL) {
                // use the default receive handler if no other was specified
                data_rcv_count += rcv_dataProc(data_rd);
            }
            else {
                // use the specified receive handler
                data_rcv_count += rcv_fptr(data_rd);
            }
        }
        );
        waitset += data_readCond;

        // init the vector for colors
        shape_colors.push_back("PURPLE");
        shape_colors.push_back("BLUE");
        shape_colors.push_back("RED");
        shape_colors.push_back("GREEN");
        shape_colors.push_back("YELLOW");
        shape_colors.push_back("CYAN");
        shape_colors.push_back("MAGENTA");
        shape_colors.push_back("ORANGE");

        for (int i = 0; i < 8; i++) {
            shape_data[i].isNew = false;
            shape_data[i].color = shape_colors.at(i);
        }
    }
}

// Receive data handler
int shapesdemo::rcv_dataProc(dds::sub::DataReader<ShapeTypeExtended>& reader)
{
    int count = 0;
    std::vector<std::string>::iterator it;
    dds::sub::LoanedSamples<ShapeTypeExtended> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            it = std::find(shape_colors.begin(), shape_colors.end(), sample.data().color());
            if (it != shape_colors.end()) {
                int idx = static_cast<int>(it - shape_colors.begin());
                shape_data[idx].x = sample.data().x();
                shape_data[idx].y = sample.data().y();
                shape_data[idx].size = sample.data().shapesize();
                shape_data[idx].angle = sample.data().angle();
                shape_data[idx].isNew = true;
            }
        }
    }
    return count;
}


/*ci
 * \brief Publish the ShapeTypeExtended topic.
 *
 * \details
 * Publish the ShapeTypeExtended topic
 *
 */
void shapesdemo::publish(void)
{ 
    data_wr.write(pub_sample); 
}


// destructor
shapesdemo::~shapesdemo() {}