/** ==================================================================
 * cros2_turtlesim_support.cxx
 * Class for interfacing a native Connext DDS application with the 
 *  ROS 2 'Turtlesim' application (as of the 'eloquent' release).
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 <arch> cros2_types.idl
 **/
#include "cros2_turtlesim_support.hpp"
 // turtleapp implementation
turtleapp::turtleapp(dds::domain::DomainParticipant participant)
    :
    tadd_rq_topic(dds::core::null), tadd_rr_topic(dds::core::null), 
    tsub_rq_topic(dds::core::null), tsub_rr_topic(dds::core::null),
    tclr_rq_topic(dds::core::null), tclr_rr_topic(dds::core::null),
    tadd_rq_wr(dds::core::null), tsub_rq_wr(dds::core::null), tclr_rq_wr(dds::core::null),
    tadd_rr_rd(dds::core::null), tsub_rr_rd(dds::core::null), tclr_rr_rd(dds::core::null),
    waitset(),
    tadd_rq_sample(), tsub_rq_sample(), tclr_rq_sample()

{
    // create topics
    tadd_rq_topic = dds::topic::Topic<turtlesim::srv::dds_::Spawn_Request_>(participant, "rq/spawnRequest");
    tadd_rr_topic = dds::topic::Topic<turtlesim::srv::dds_::Spawn_Response_>(participant, "rr/spawnReply");
    tsub_rq_topic = dds::topic::Topic<turtlesim::srv::dds_::Kill_Request_>(participant, "rq/killRequest");
    tsub_rr_topic = dds::topic::Topic<turtlesim::srv::dds_::Kill_Response_>(participant, "rr/killReply");
    // clear the turtlesim screen
    tclr_rq_topic = dds::topic::Topic<std_srvs::srv::dds_::Empty_Request_>(participant, "rq/clearRequest");
    tclr_rr_topic = dds::topic::Topic<std_srvs::srv::dds_::Empty_Response_>(participant, "rr/clearReply");

    // Create DataWriters for turtle topics ----------------------------------------
    tadd_rq_wr = dds::pub::DataWriter<turtlesim::srv::dds_::Spawn_Request_>(dds::pub::Publisher(participant), tadd_rq_topic);
    tsub_rq_wr = dds::pub::DataWriter<turtlesim::srv::dds_::Kill_Request_>(dds::pub::Publisher(participant), tsub_rq_topic);
    tclr_rq_wr = dds::pub::DataWriter<std_srvs::srv::dds_::Empty_Request_>(dds::pub::Publisher(participant), tclr_rq_topic);

    // Create DataReaders for turtle topics ----------------------------------------
    tadd_rr_rd = dds::sub::DataReader<turtlesim::srv::dds_::Spawn_Response_>(dds::sub::Subscriber(participant), tadd_rr_topic);
    tsub_rr_rd = dds::sub::DataReader<turtlesim::srv::dds_::Kill_Response_>(dds::sub::Subscriber(participant), tsub_rr_topic);
    tclr_rr_rd = dds::sub::DataReader<std_srvs::srv::dds_::Empty_Response_>(dds::sub::Subscriber(participant), tclr_rr_topic);

    // Create ReadConditions and associate handlers for received data --------------
    // Turtle spawn response 
    dds::sub::cond::ReadCondition tadd_readCond(
        tadd_rr_rd, dds::sub::status::DataState::any(),
        [this](/* dds::core::cond::Condition condition */)
    {
        spawn_resp_count += tadd_dataProc(tadd_rr_rd);
    }
    );
    waitset += tadd_readCond;

    // Turtle retire response
    dds::sub::cond::ReadCondition tsub_readCond(
        tsub_rr_rd, dds::sub::status::DataState::any(),
        [this](/* dds::core::cond::Condition condition */)
    {
        retire_resp_count += tsub_dataProc(tsub_rr_rd);
    }
    );
    waitset += tsub_readCond;

    // Turtle clearscreen response
    dds::sub::cond::ReadCondition tclr_readCond(
        tclr_rr_rd, dds::sub::status::DataState::any(),
        [this](/* dds::core::cond::Condition condition */)
    {
        clear_resp_count += tclr_dataProc(tclr_rr_rd);
    }
    );
    waitset += tclr_readCond;

    // Initialize DDS samples for writing ------------------------------------------
    // spawn turtle
    // retire turtle
    tsub_rq_sample.name("roomGen");
}

// Receive data processors
int turtleapp::tadd_dataProc(dds::sub::DataReader<turtlesim::srv::dds_::Spawn_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::srv::dds_::Spawn_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            // std::cout << "addTurtle " << sample.data() << std::endl;
        }
    }
    return count;
}
int turtleapp::tsub_dataProc(dds::sub::DataReader<turtlesim::srv::dds_::Kill_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::srv::dds_::Kill_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            //std::cout << "retireTurtle " << sample.data() << std::endl;
        }
    }
    return count;
}
int turtleapp::tclr_dataProc(dds::sub::DataReader<std_srvs::srv::dds_::Empty_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<std_srvs::srv::dds_::Empty_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            //std::cout << "clr " << sample.data() << std::endl;
        }
    }
    return count;
}

// clear the turtlesim screen
void turtleapp::clear_screen(void)
{
    // clear the turtlesim display
    tclr_rq_wr.write(tclr_rq_sample);

}

// spawn the (pre-named) turtle
void turtleapp::spawn_turtle(std::string turtleName, float x, float y)
{
    tadd_rq_sample.name(turtleName);
    tadd_rq_sample.x(x);
    tadd_rq_sample.y(y);
    tadd_rq_sample.theta(0);
    tadd_rq_wr.write(tadd_rq_sample);
}

// retire the turtle
void turtleapp::retire_turtle(std::string turtleName)
{
    tsub_rq_sample.name(turtleName);
    tsub_rq_wr.write(tsub_rq_sample);
    waitset.dispatch(dds::core::Duration(2));
}

// destructor
turtleapp::~turtleapp() {}

// ########################################################################################################
 // turtleinst implementation
turtleinst::turtleinst(const std::string turtleName, uint32_t opt_en, dds::domain::DomainParticipant participant)
    :
    tmov_topic(dds::core::null), tmov_wr(dds::core::null), tmov_sample(),

    ttpa_rq_topic(dds::core::null), ttpa_rr_topic(dds::core::null), ttpa_rq_wr(dds::core::null), ttpa_rr_rd(dds::core::null),
    ttpa_rq_sample(),
    ttpr_rq_topic(dds::core::null), ttpr_rr_topic(dds::core::null), ttpr_rq_wr(dds::core::null), ttpr_rr_rd(dds::core::null),
    ttpr_rq_sample(),

    trot_goal_rq_topic(dds::core::null), trot_goal_rr_topic(dds::core::null), trot_res_rq_topic(dds::core::null), 
    trot_res_rr_topic(dds::core::null), trot_fb_topic(dds::core::null),
    trot_goal_wr(dds::core::null), trot_res_wr(dds::core::null), 
    trot_goal_rr_rd(dds::core::null), trot_res_rr_rd(dds::core::null), trot_fb_rd(dds::core::null),

    tpen_rq_topic(dds::core::null), tpen_rr_topic(dds::core::null), tpen_rq_wr(dds::core::null), tpen_rr_rd(dds::core::null),
    tpen_rq_sample(),

    tpos_topic(dds::core::null), tpos_rd(dds::core::null),
    tcolor_topic(dds::core::null), tcolor_rd(dds::core::null),
    waitset()

{
    /* Turtle support components can be enabled using the bitfield opt_en,
        bits are enumerated by enum turtleinst_enable.
       Create the Topics/DataWriters/DataReaders/ReadConditions for each enabled component. 
    */ 
    myInstName = turtleName;
    op_delay_nsecs = 10000000;
    op_waitset_timeout_nsecs = 50000000;

    // MOVE(Twist) (ROS 2 message)
    if (opt_en & (1 << MOVE_PUB)) {
        // Topics
        const std::string tmov_topname("rt/" + turtleName + "/cmd_vel");
        tmov_topic = dds::topic::Topic<geometry_msgs::msg::dds_::Twist_>(participant, tmov_topname);

        // DataWriter
        tmov_wr = dds::pub::DataWriter<geometry_msgs::msg::dds_::Twist_>(dds::pub::Publisher(participant), tmov_topic);
    }

    // Teleport to absolute location (ROS 2 service) -------------------------
    if (opt_en & (1 << TELEPORT_ABS)) {
        // Topics
        const std::string ttpa_rq_topname("rq/" + turtleName + "/teleport_absoluteRequest");
        ttpa_rq_topic = dds::topic::Topic<turtlesim::srv::dds_::TeleportAbsolute_Request_>(participant, ttpa_rq_topname);
        const std::string ttpa_rr_topname("rr/" + turtleName + "/teleport_absoluteReply");
        ttpa_rr_topic = dds::topic::Topic<turtlesim::srv::dds_::TeleportAbsolute_Response_>(participant, ttpa_rr_topname);

        // DataWriters/DataReaders & ReadConditions
        ttpa_rq_wr = dds::pub::DataWriter<turtlesim::srv::dds_::TeleportAbsolute_Request_>(dds::pub::Publisher(participant), ttpa_rq_topic);
        ttpa_rr_rd = dds::sub::DataReader<turtlesim::srv::dds_::TeleportAbsolute_Response_>(dds::sub::Subscriber(participant), ttpa_rr_topic);
        dds::sub::cond::ReadCondition ttpa_readCond(
            ttpa_rr_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            tele_abs_resp_count += ttpa_dataProc(ttpa_rr_rd);
        }
        );
        waitset += ttpa_readCond;
    }

    // Teleport to relative location (ROS 2 service) -------------------------
    if (opt_en & (1 << TELEPORT_REL)) {
        // Topics
        const std::string ttpr_rq_topname("rq/" + turtleName + "/teleport_relativeRequest");
        ttpr_rq_topic = dds::topic::Topic<turtlesim::srv::dds_::TeleportRelative_Request_>(participant, ttpr_rq_topname);
        const std::string ttpr_rr_topname("rr/" + turtleName + "/teleport_relativeReply");
        ttpr_rr_topic = dds::topic::Topic<turtlesim::srv::dds_::TeleportRelative_Response_>(participant, ttpr_rr_topname);

        // DataWriters/DataReaders & ReadConditions
        ttpr_rq_wr = dds::pub::DataWriter<turtlesim::srv::dds_::TeleportRelative_Request_>(dds::pub::Publisher(participant), ttpr_rq_topic);
        ttpr_rr_rd = dds::sub::DataReader<turtlesim::srv::dds_::TeleportRelative_Response_>(dds::sub::Subscriber(participant), ttpr_rr_topic);
        dds::sub::cond::ReadCondition ttpr_readCond(
            ttpr_rr_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            tele_rel_resp_count += ttpr_dataProc(ttpr_rr_rd);
        }
        );
        waitset += ttpr_readCond;
    }

    // Rotate to absolute orientation (ROS 2 action) -------------------------
    if (opt_en & (1 << ROTATE_ABS)) {
        // Topics
        const std::string trot_goal_rq_topname("rq/" + turtleName + "/rotate_absolute/_action/send_goalRequest");
        trot_goal_rq_topic = dds::topic::Topic<turtlesim::action::dds_::RotateAbsolute_SendGoal_Request_>(participant, trot_goal_rq_topname);
        const std::string trot_goal_rr_topname("rr/" + turtleName + "/rotate_absolute/_action/send_goalReply");
        trot_goal_rr_topic = dds::topic::Topic<turtlesim::action::dds_::RotateAbsolute_SendGoal_Response_>(participant, trot_goal_rr_topname);
        const std::string trot_res_rq_topname("rq/" + turtleName + "/rotate_absolute/_action/get_resultRequest");
        trot_res_rq_topic = dds::topic::Topic<turtlesim::action::dds_::RotateAbsolute_GetResult_Request_>(participant, trot_res_rq_topname);
        const std::string trot_res_rr_topname("rr/" + turtleName + "/rotate_absolute/_action/get_resultReply");
        trot_res_rr_topic = dds::topic::Topic<turtlesim::action::dds_::RotateAbsolute_GetResult_Response_>(participant, trot_res_rr_topname);
        const std::string trot_fb_topname("rt/" + turtleName + "/rotate_absolute/_action/feedback");
        trot_fb_topic = dds::topic::Topic<turtlesim::action::dds_::RotateAbsolute_FeedbackMessage_>(participant, trot_fb_topname);

        // DataWriters/DataReaders & ReadConditions
        trot_goal_wr = dds::pub::DataWriter<turtlesim::action::dds_::RotateAbsolute_SendGoal_Request_>(dds::pub::Publisher(participant), trot_goal_rq_topic);
        trot_res_wr = dds::pub::DataWriter<turtlesim::action::dds_::RotateAbsolute_GetResult_Request_>(dds::pub::Publisher(participant), trot_res_rq_topic);
        trot_goal_rr_rd = dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_SendGoal_Response_>(dds::sub::Subscriber(participant), trot_goal_rr_topic);
        trot_res_rr_rd = dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_GetResult_Response_>(dds::sub::Subscriber(participant), trot_res_rr_topic);
        trot_fb_rd = dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_FeedbackMessage_>(dds::sub::Subscriber(participant), trot_fb_topic);
        dds::sub::cond::ReadCondition trot_setgoal_readCond(
            trot_goal_rr_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            trot_goal_resp_count += trot_goal_dataProc(trot_goal_rr_rd);
        }
        );
        waitset += trot_setgoal_readCond;
        // Turtle rotate result response
        dds::sub::cond::ReadCondition trot_atgoal_readCond(
            trot_res_rr_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            trot_res_resp_count += trot_res_dataProc(trot_res_rr_rd);
        }
        );
        waitset += trot_atgoal_readCond;
        // Turtle rotate feedback
        dds::sub::cond::ReadCondition trot_feedback_readCond(
            trot_fb_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            trot_fb_count += trot_fb_dataProc(trot_fb_rd);
        }
        );
        waitset += trot_feedback_readCond;
    }
    
    // Pen color/size (ROS 2 service) ----------------------------------------
    if (opt_en & (1 << PEN_SET)) {
        // Topics
        const std::string tpen_rq_topname("rq/" + turtleName + "/set_penRequest");
        tpen_rq_topic = dds::topic::Topic<turtlesim::srv::dds_::SetPen_Request_>(participant, tpen_rq_topname);
        const std::string tpen_rr_topname("rr/" + turtleName + "/set_penReply");
        tpen_rr_topic = dds::topic::Topic<turtlesim::srv::dds_::SetPen_Response_>(participant, tpen_rr_topname);

        // DataWriters/DataReaders & ReadConditions
        tpen_rq_wr = dds::pub::DataWriter<turtlesim::srv::dds_::SetPen_Request_>(dds::pub::Publisher(participant), tpen_rq_topic);
        tpen_rr_rd = dds::sub::DataReader<turtlesim::srv::dds_::SetPen_Response_>(dds::sub::Subscriber(participant), tpen_rr_topic);
        dds::sub::cond::ReadCondition tpen_readCond(
            tpen_rr_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            pen_resp_count += tpen_dataProc(tpen_rr_rd);
        }
        );
        waitset += tpen_readCond;
    }
    
    // Turtle pose/position (ROS 2 message) ----------------------------------
    if (opt_en & (1 << POSE_SUB)) {
        const std::string tpos_topname("rt/" + turtleName + "/pose");
        tpos_topic = dds::topic::Topic<turtlesim::msg::dds_::Pose_>(participant, tpos_topname);
        tpos_rd = dds::sub::DataReader<turtlesim::msg::dds_::Pose_>(dds::sub::Subscriber(participant), tpos_topic);

        dds::sub::cond::ReadCondition tpos_readCond(
            tpos_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            pose_rcv_count += tpos_dataProc(tpos_rd);
        }
        );
        waitset += tpos_readCond;
    }
    
    // Turtle ... pen color? (ROS 2 message) ---------------------------------
    if (opt_en & (1 << COLOR_SUB)) {
        const std::string tcolor_topname("rt/" + turtleName + "/color_sensor");
        tcolor_topic = dds::topic::Topic<turtlesim::msg::dds_::Color_>(participant, tcolor_topname);
        tcolor_rd = dds::sub::DataReader<turtlesim::msg::dds_::Color_>(dds::sub::Subscriber(participant), tcolor_topic);

        dds::sub::cond::ReadCondition tcolor_readCond(
            tcolor_rd, dds::sub::status::DataState::any(),
            [this](/* dds::core::cond::Condition condition */)
        {
            tcolor_rcv_count += tcolor_dataProc(tcolor_rd);
        }
        );
        waitset += tcolor_readCond;
    }
    
}

// Received data handlers ----------------------------------------------------
// turtle pose (position and orientation) update message
int turtleinst::tpos_dataProc(dds::sub::DataReader<turtlesim::msg::dds_::Pose_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::msg::dds_::Pose_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            
            myPose.x = sample.data().x();
            myPose.y = sample.data().y();
            myPose.theta = sample.data().theta();
            myPose.lvel = sample.data().linear_velocity();
            myPose.avel = sample.data().angular_velocity();
            myPose.poseCount++;
            myPose.isNew = true;
            count++;
            //std::cout << "Pose: (" << myInstName << ") " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: Teleport Absolute Request response
int turtleinst::ttpa_dataProc(dds::sub::DataReader<turtlesim::srv::dds_::TeleportAbsolute_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::srv::dds_::TeleportAbsolute_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            //std::cout << "teleport-a " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: Teleport Relative Request response
int turtleinst::ttpr_dataProc(dds::sub::DataReader<turtlesim::srv::dds_::TeleportRelative_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::srv::dds_::TeleportRelative_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            std::cout << "teleport-r " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: Set Pen Request response
int turtleinst::tpen_dataProc(dds::sub::DataReader<turtlesim::srv::dds_::SetPen_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::srv::dds_::SetPen_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            // std::cout << "pen " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: Turtle rotate set goal request response
int turtleinst::trot_goal_dataProc(dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_SendGoal_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::action::dds_::RotateAbsolute_SendGoal_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            std::cout << "ROTg: " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: Turtle rotate goal reached request response
int turtleinst::trot_res_dataProc(dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_GetResult_Response_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::action::dds_::RotateAbsolute_GetResult_Response_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            std::cout << "ROTr " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: turtle rotate feedback message
int turtleinst::trot_fb_dataProc(dds::sub::DataReader<turtlesim::action::dds_::RotateAbsolute_FeedbackMessage_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::action::dds_::RotateAbsolute_FeedbackMessage_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            //std::cout << "ROTfb " << sample.data() << std::endl;
        }
    }
    return count;
}

// Received data handler: turtle color sensor
int turtleinst::tcolor_dataProc(dds::sub::DataReader<turtlesim::msg::dds_::Color_>& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<turtlesim::msg::dds_::Color_> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            std::cout << "Color: " << sample.data() << std::endl;
        }
    }
    return count;
}

// ===========================================================================
// member functions (FIXME: MOVE THIS TO A DERIVED CLASS, OUTSIDE OF THIS FILE)
// turtle pen control ----------------------------------------------
// pen on/off
void turtleinst::turtle_pen_set(bool ink_on)
{
    tpen_rq_sample.off(!ink_on);
    tpen_rq_wr.write(tpen_rq_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}
// pen width
void turtleinst::turtle_pen_set(uint8_t lineWidth)
{
    tpen_rq_sample.width(lineWidth);
    tpen_rq_wr.write(tpen_rq_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}
// pen color
void turtleinst::turtle_pen_set(uint32_t rgb8_color)
{
    tpen_rq_sample.r((uint8_t)((rgb8_color >> 16) & 0xff));
    tpen_rq_sample.g((uint8_t)((rgb8_color >> 8) & 0xff));
    tpen_rq_sample.b((uint8_t)((rgb8_color >> 0) & 0xff));
    tpen_rq_wr.write(tpen_rq_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}
// pen color and width
void turtleinst::turtle_pen_set(uint32_t rgb8_color, uint8_t lineWidth)
{
    tpen_rq_sample.r((uint8_t)((rgb8_color >> 16) & 0xff));
    tpen_rq_sample.g((uint8_t)((rgb8_color >>  8) & 0xff));
    tpen_rq_sample.b((uint8_t)((rgb8_color >>  0) & 0xff));
    tpen_rq_sample.width(lineWidth);
    tpen_rq_wr.write(tpen_rq_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}
// turtle teleport to absolute XY location, optional rotate turtle to theta value
void turtleinst::turtle_teleport_xy(float x, float y, float theta)
{
    ttpa_rq_sample.x(x);
    ttpa_rq_sample.y(y);
    ttpa_rq_sample.theta(theta);
    ttpa_rq_wr.write(ttpa_rq_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}

// turtle move(Twist) forward/reverse with optional turn
void turtleinst::turtle_move_and_turn(double forward, double turn)
{
    tmov_sample.linear().x(forward);
    tmov_sample.angular().z(turn);
    tmov_wr.write(tmov_sample);
    rti::util::sleep(dds::core::Duration(0, op_delay_nsecs));
    waitset.dispatch(dds::core::Duration(0, op_waitset_timeout_nsecs));
}

turtleinst::~turtleinst() {}

