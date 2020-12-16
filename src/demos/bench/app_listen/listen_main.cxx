/*******************************************************************************
 (c) 2005-2015 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 RTI grants Licensee a license to use, modify, compile, and create derivative
 works of the Software.  Licensee has the right to distribute object form only
 for use with RTI products.  The Software is provided "as is", with no warranty
 of any type, including any warranty for fitness for any purpose. RTI is under
 no obligation to maintain or support the Software.  RTI shall not be liable for
 any incidental or consequential damages arising out of the use or inability to
 use the software.
 ******************************************************************************/

#include <iostream>
#include "cros2_types.hpp"
#include <dds/dds.hpp>
#include <rti/core/ListenerBinder.hpp>

class MyParticipantListener : public dds::domain::NoOpDomainParticipantListener {
public:
    virtual void on_requested_deadline_missed(
            dds::pub::AnyDataWriter &writer,
            const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        std::cout << "ParticipantListener: on_requested_deadline_missed()"
                  << std::endl;
    }

    virtual void on_offered_incompatible_qos(
            dds::pub::AnyDataWriter &writer,
            const ::dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        std::cout << "ParticipantListener: on_offered_incompatible_qos()"
                  << std::endl;
    }

    virtual void on_sample_rejected(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "ParticipantListener: on_sample_rejected()" << std::endl;
    }

    virtual void on_liveliness_changed(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "ParticipantListener: on_liveliness_changed()"
                  << std::endl;
    }


    virtual void on_sample_lost(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "ParticipantListener: on_sample_lost()" << std::endl;
    }

    virtual void on_subscription_matched(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "ParticipantListener: on_subscription_matched()"
                  << std::endl;
    }

    virtual void on_data_available(dds::sub::AnyDataReader &the_reader)
    {
        std::cout << "ParticipantListener: on_data_available()" << std::endl;
    }


    virtual void on_data_on_readers(dds::sub::Subscriber &sub)
    {
        // Notify DataReaders only calls on_data_available for
        // DataReaders with unread samples.
        sub.notify_datareaders();
        std::cout << "ParticipantListener: on_data_on_readers()" << std::endl;
    }

    virtual void on_inconsistent_topic(
            dds::topic::AnyTopic &topic,
            const dds::core::status::InconsistentTopicStatus &status)
    {
        std::cout << "ParticipantListener: on_inconsistent_topic()"
                  << std::endl;
    }
};

class MySubscriberListener : public dds::sub::NoOpSubscriberListener {
public:
    virtual void on_requested_deadline_missed(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        std::cout << "SubscriberListener: on_requested_deadline_missed()"
                  << std::endl;
    }

    virtual void on_requested_incompatible_qos(
            dds::sub::AnyDataReader &the_reader,
            const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        std::cout << "SubscriberListener: on_requested_incompatible_qos()"
                  << std::endl;
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "SubscriberListener: on_sample_rejected()" << std::endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader &the_reader,
            const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "SubscriberListener: on_liveliness_changed()" << std::endl;
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "SubscriberListener: on_sample_lost()" << std::endl;
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader &the_reader,
            const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "SubscriberListener: on_subscription_matched()"
                  << std::endl;
    }

    virtual void on_data_available(dds::sub::AnyDataReader &the_reader)
    {
        std::cout << "SubscriberListener: on_data_available()" << std::endl;
    }

    virtual void on_data_on_readers(dds::sub::Subscriber &sub)
    {
        static int count = 0;
        std::cout << "SubscriberListener: on_data_on_readers()" << std::endl;

        sub->notify_datareaders();
        if (++count > 3) {
            dds::core::status::StatusMask new_mask = dds::core::status::StatusMask::all();
            new_mask &= ~dds::core::status::StatusMask::data_on_readers();
            sub.listener(this, new_mask);
        }
    }
};

class MyDataReaderListener : public dds::sub::NoOpDataReaderListener<sensor_msgs::msg::dds_::PointCloud2_> {
    virtual void on_requested_deadline_missed(
            dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        std::cout << "ReaderListener: on_requested_deadline_missed()"
                  << std::endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        std::cout << "ReaderListener: on_requested_incompatible_qos()"
                  << std::endl;
    }

    virtual void on_sample_rejected(
        dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "ReaderListener: on_sample_rejected()" << std::endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "ReaderListener: on_liveliness_changed()" << std::endl
                  << "  Alive writers: " << status.alive_count() << std::endl;
    }

    virtual void on_sample_lost(
        dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "ReaderListener: on_sample_lost()" << std::endl;
    }

    virtual void on_subscription_matched(
        dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader,
            const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "ReaderListener: on_subscription_matched()" << std::endl;
    }

    virtual void on_data_available(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> &reader)
    {
        dds::sub::LoanedSamples<sensor_msgs::msg::dds_::PointCloud2_> samples = reader.take();
        for (dds::sub::LoanedSamples<sensor_msgs::msg::dds_::PointCloud2_>::iterator sampleIt = samples.begin();
             sampleIt != samples.end();
             ++sampleIt) {
            // If the reference we get is valid data, it means we have actual
            // data available, otherwise we got metadata.
            if (sampleIt->info().valid()) {
                std::cout << " ## Data Received ## " << std::endl;
                // std::cout << sampleIt->data() << std::endl;
            } else {
                std::cout << "  Got metadata" << std::endl;
            }
        }
    }
};

class MyDataWriterListener : public dds::pub::NoOpDataWriterListener<sensor_msgs::msg::dds_::PointCloud2_> {
public:
    virtual void on_offered_deadline_missed(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        std::cout << "DataWriterListener: on_offered_deadline_missed()"
                  << std::endl;
    }

    virtual void on_liveliness_lost(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const dds::core::status::LivelinessLostStatus &status)
    {
        std::cout << "DataWriterListener: on_liveliness_lost()" << std::endl;
    }

    virtual void on_offered_incompatible_qos(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        std::cout << "DataWriterListener: on_offered_incompatible_qos()"
                  << std::endl;
    }

    virtual void on_publication_matched(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const dds::core::status::PublicationMatchedStatus &status)
    {
        std::cout << "DataWriterListener: on_publication_matched()"
                  << std::endl;
        if (status.current_count_change() < 0) {
            std::cout << "lost a subscription" << std::endl;
        } else {
            std::cout << "found a subscription" << std::endl;
        }
    }

    virtual void on_reliable_writer_cache_changed(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const rti::core::status::ReliableWriterCacheChangedStatus &status)
    {
        std::cout << "DataWriterListener: on_reliable_writer_cache_changed()"
                  << std::endl;
    }

    virtual void on_reliable_reader_activity_changed(
            dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> &writer,
            const rti::core::status::ReliableReaderActivityChangedStatus
                    &status)
    {
        std::cout << "DataWriterListener: on_reliable_reader_activity_changed()"
                  << std::endl;
    }
};

void participant_main(int domain_id, int sample_count)
{
    // Create the participant
    dds::domain::DomainParticipant participant(domain_id);
    
    // Create the publisher
    // To customize QoS, use the configuration file USER_QOS_PROFILES.xml
    dds::pub::Publisher publisher(participant);

    // To customize topic QoS, use the configuration file USER_QOS_PROFILES.xml
    dds::topic::Topic<sensor_msgs::msg::dds_::PointCloud2_> sub_topic(participant, "rt/cloud_call");
    dds::topic::Topic<sensor_msgs::msg::dds_::PointCloud2_> pub_topic(participant, "rt/cloud_echo");


    // We will use the Data Writer Listener defined above to print
    // a message when some of events are triggered in the DataWriter.
    // By using ListenerBinder (a RAII) it will take care of setting the
    // listener to NULL on destruction.
#if 0   // bounded
    dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> writer(publisher, pub_topic);
#else   // unbounded support
    dds::pub::qos::DataWriterQos writer_qos = dds::core::QosProvider::Default().datawriter_qos();
    writer_qos.policy<rti::core::policy::Property>().set({ "dds.data_writer.history.memory_manager.fast_pool.pool_buffer_max_size", "1048576" });
    dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> writer(publisher, pub_topic, writer_qos);
#endif
    rti::core::ListenerBinder<dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_>> writer_listener =
            rti::core::bind_and_manage_listener(
                    writer,
                    new MyDataWriterListener,
                    dds::core::status::StatusMask::all());

    // Create data sample for writing
    sensor_msgs::msg::dds_::PointCloud2_ pub_sample;
    

    // Associate a listener to the participant using ListenerBinder, a RAII that
    // will take care of setting it to NULL on destruction.
    rti::core::ListenerBinder<dds::domain::DomainParticipant> participant_listener =
            rti::core::bind_and_manage_listener(
                    participant,
                    new MyParticipantListener,
                    dds::core::status::StatusMask::all());


    // Create the subscriber and associate a listener
    dds::sub::Subscriber subscriber(participant);
    rti::core::ListenerBinder<dds::sub::Subscriber> subscriber_listener =
            rti::core::bind_and_manage_listener(
                    subscriber,
                    new MySubscriberListener,
                    dds::core::status::StatusMask::all());

    // Create the DataReader and associate a listener
    dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> reader(subscriber, sub_topic);
    rti::core::ListenerBinder<dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_>> datareader_listener =
            rti::core::bind_and_manage_listener(
                    reader,
                    new MyDataReaderListener,
                    dds::core::status::StatusMask::all());

    // init the data sample for pub
    pub_sample.height_(1);
    pub_sample.width_(1);

    // Main loop
    for (int count = 0; (sample_count == 0) || (count < sample_count);
         ++count) {
          
        // Modify data and send it.
        pub_sample.height_(1);
        writer.write(pub_sample);
          
        // Each "sample_count" is four seconds.
        rti::util::sleep(dds::core::Duration(4));
    }
}

int main(int argc, char *argv[])
{
    int domain_id = 0;
    int sample_count = 0;  // Infinite loop

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }

    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    // To turn on additional logging, include <rti/config/Logger.hpp> and
    // uncomment the following line:
    // rti::config::Logger::instance().verbosity(rti::config::Verbosity::STATUS_ALL);

    try {
        participant_main(domain_id, sample_count);
    } catch (std::exception ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}