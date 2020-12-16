

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ShapeType.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include <iosfwd>
#include <iomanip>

#include "rti/topic/cdr/Serialization.hpp"

#include "ShapeType.hpp"
#include "ShapeTypePlugin.hpp"

#include <rti/util/ostream_operators.hpp>

std::ostream& operator << (std::ostream& o,const ShapeFillKind& sample)
{
    ::rti::util::StreamFlagSaver flag_saver (o);
    switch(sample.underlying()){
        case ShapeFillKind::SOLID_FILL:
        o << "ShapeFillKind::SOLID_FILL" << " ";
        break;
        case ShapeFillKind::TRANSPARENT_FILL:
        o << "ShapeFillKind::TRANSPARENT_FILL" << " ";
        break;
        case ShapeFillKind::HORIZONTAL_HATCH_FILL:
        o << "ShapeFillKind::HORIZONTAL_HATCH_FILL" << " ";
        break;
        case ShapeFillKind::VERTICAL_HATCH_FILL:
        o << "ShapeFillKind::VERTICAL_HATCH_FILL" << " ";
        break;
    }
    return o;
}

// ---- ShapeType: 

ShapeType::ShapeType() :
    m_color_ ("") ,
    m_x_ (0) ,
    m_y_ (0) ,
    m_shapesize_ (0)  {
}   

ShapeType::ShapeType (
    const std::string& color,
    int32_t x,
    int32_t y,
    int32_t shapesize)
    :
        m_color_( color ),
        m_x_( x ),
        m_y_( y ),
        m_shapesize_( shapesize ) {
}

#ifdef RTI_CXX11_RVALUE_REFERENCES
#ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
ShapeType::ShapeType(ShapeType&& other_) OMG_NOEXCEPT  :m_color_ (std::move(other_.m_color_))
,
m_x_ (std::move(other_.m_x_))
,
m_y_ (std::move(other_.m_y_))
,
m_shapesize_ (std::move(other_.m_shapesize_))
{
} 

ShapeType& ShapeType::operator=(ShapeType&&  other_) OMG_NOEXCEPT {
    ShapeType tmp(std::move(other_));
    swap(tmp); 
    return *this;
}
#endif
#endif   

void ShapeType::swap(ShapeType& other_)  OMG_NOEXCEPT 
{
    using std::swap;
    swap(m_color_, other_.m_color_);
    swap(m_x_, other_.m_x_);
    swap(m_y_, other_.m_y_);
    swap(m_shapesize_, other_.m_shapesize_);
}  

bool ShapeType::operator == (const ShapeType& other_) const {
    if (m_color_ != other_.m_color_) {
        return false;
    }
    if (m_x_ != other_.m_x_) {
        return false;
    }
    if (m_y_ != other_.m_y_) {
        return false;
    }
    if (m_shapesize_ != other_.m_shapesize_) {
        return false;
    }
    return true;
}
bool ShapeType::operator != (const ShapeType& other_) const {
    return !this->operator ==(other_);
}

std::ostream& operator << (std::ostream& o,const ShapeType& sample)
{
    ::rti::util::StreamFlagSaver flag_saver (o);
    o <<"[";
    o << "color: " << sample.color()<<", ";
    o << "x: " << sample.x()<<", ";
    o << "y: " << sample.y()<<", ";
    o << "shapesize: " << sample.shapesize() ;
    o <<"]";
    return o;
}

// ---- ShapeTypeExtended: 

ShapeTypeExtended::ShapeTypeExtended() :
    m_fillKind_(ShapeFillKind::SOLID_FILL) ,
    m_angle_ (0.0f)  {
}   

ShapeTypeExtended::ShapeTypeExtended (
    const std::string& color,
    int32_t x,
    int32_t y,
    int32_t shapesize,
    const ShapeFillKind& fillKind,
    float angle)
    :
        ShapeType(color,x,y,shapesize ),
        m_fillKind_( fillKind ),
        m_angle_( angle ) {
}

#ifdef RTI_CXX11_RVALUE_REFERENCES
#ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
ShapeTypeExtended::ShapeTypeExtended(ShapeTypeExtended&& other_) OMG_NOEXCEPT  : 
ShapeType(std::move(other_)),
m_fillKind_ (std::move(other_.m_fillKind_))
,
m_angle_ (std::move(other_.m_angle_))
{
} 

ShapeTypeExtended& ShapeTypeExtended::operator=(ShapeTypeExtended&&  other_) OMG_NOEXCEPT {
    ShapeTypeExtended tmp(std::move(other_));
    swap(tmp); 
    return *this;
}
#endif
#endif   

void ShapeTypeExtended::swap(ShapeTypeExtended& other_)  OMG_NOEXCEPT 
{
    using std::swap;
    ShapeType::swap(other_);
    swap(m_fillKind_, other_.m_fillKind_);
    swap(m_angle_, other_.m_angle_);
}  

bool ShapeTypeExtended::operator == (const ShapeTypeExtended& other_) const {
    if (!ShapeType::operator == (other_)){
        return false;
    }
    if (m_fillKind_ != other_.m_fillKind_) {
        return false;
    }
    if (m_angle_ != other_.m_angle_) {
        return false;
    }
    return true;
}
bool ShapeTypeExtended::operator != (const ShapeTypeExtended& other_) const {
    return !this->operator ==(other_);
}

std::ostream& operator << (std::ostream& o,const ShapeTypeExtended& sample)
{
    ::rti::util::StreamFlagSaver flag_saver (o);
    o <<"[";
    o << static_cast<const ShapeType &>(sample);
    o << "fillKind: " << sample.fillKind()<<", ";
    o << "angle: " << std::setprecision(9) <<sample.angle() ;
    o <<"]";
    return o;
}

// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        #ifndef NDDS_STANDALONE_TYPE

        template<>
        struct native_type_code< ShapeFillKind > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode_Member ShapeFillKind_g_tc_members[4]=
                {

                    {
                        (char *)"SOLID_FILL",/* Member name */
                        {
                            0, /* Ignored */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        ShapeFillKind::SOLID_FILL, 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PRIVATE_MEMBER,/* Member visibility */ 

                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"TRANSPARENT_FILL",/* Member name */
                        {
                            0, /* Ignored */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        ShapeFillKind::TRANSPARENT_FILL, 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PRIVATE_MEMBER,/* Member visibility */ 

                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"HORIZONTAL_HATCH_FILL",/* Member name */
                        {
                            0, /* Ignored */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        ShapeFillKind::HORIZONTAL_HATCH_FILL, 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PRIVATE_MEMBER,/* Member visibility */ 

                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VERTICAL_HATCH_FILL",/* Member name */
                        {
                            0, /* Ignored */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        ShapeFillKind::VERTICAL_HATCH_FILL, 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PRIVATE_MEMBER,/* Member visibility */ 

                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ShapeFillKind_g_tc =
                {{
                        DDS_TK_ENUM, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ShapeFillKind", /* Name */
                        NULL,     /* Base class type code is assigned later */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        4, /* Number of members */
                        ShapeFillKind_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Type Modifier */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ShapeFillKind*/

                if (is_initialized) {
                    return &ShapeFillKind_g_tc;
                }

                ShapeFillKind_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                /* Initialize the values for annotations. */
                ShapeFillKind_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_ENUM;
                ShapeFillKind_g_tc._data._annotations._defaultValue._u.long_value = 0;

                ShapeFillKind_g_tc._data._sampleAccessInfo = sample_access_info();
                ShapeFillKind_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized = RTI_TRUE;

                return &ShapeFillKind_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static RTIXCdrMemberAccessInfo ShapeFillKind_g_memberAccessInfos[1] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ShapeFillKind_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &ShapeFillKind_g_sampleAccessInfo;
                }

                ShapeFillKind_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

                ShapeFillKind_g_sampleAccessInfo.memberAccessInfos = 
                ShapeFillKind_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(ShapeFillKind);

                    if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
                        ShapeFillKind_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrUnsignedLong_MAX;
                    } else {
                        ShapeFillKind_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ShapeFillKind_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ShapeFillKind_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ShapeFillKind >;

                ShapeFillKind_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &ShapeFillKind_g_sampleAccessInfo;
            }

            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ShapeFillKind_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ShapeFillKind_g_typePlugin;
            }
        }; // native_type_code
        #endif

        const ::dds::core::xtypes::EnumType& dynamic_type< ShapeFillKind >::get()
        {
            return static_cast<const ::dds::core::xtypes::EnumType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ShapeFillKind >::get())));
        }

        #ifndef NDDS_STANDALONE_TYPE

        template<>
        struct native_type_code< ShapeType > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode ShapeType_g_tc_color_string;

                static DDS_TypeCode_Member ShapeType_g_tc_members[4]=
                {

                    {
                        (char *)"color",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"x",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"y",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"shapesize",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ShapeType_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ShapeType", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        4, /* Number of members */
                        ShapeType_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ShapeType*/

                if (is_initialized) {
                    return &ShapeType_g_tc;
                }

                ShapeType_g_tc_color_string = initialize_string_typecode((128));

                ShapeType_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ShapeType_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ShapeType_g_tc_color_string;
                ShapeType_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ShapeType_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ShapeType_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

                /* Initialize the values for member annotations. */
                ShapeType_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ShapeType_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

                ShapeType_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
                ShapeType_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ShapeType_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

                ShapeType_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[2]._annotations._defaultValue._u.long_value = 0;
                ShapeType_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[2]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ShapeType_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[2]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

                ShapeType_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
                ShapeType_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ShapeType_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ShapeType_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

                ShapeType_g_tc._data._sampleAccessInfo = sample_access_info();
                ShapeType_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized = RTI_TRUE;

                return &ShapeType_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                ShapeType *sample;

                static RTIXCdrMemberAccessInfo ShapeType_g_memberAccessInfos[4] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ShapeType_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &ShapeType_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ShapeType);
                if (sample == NULL) {
                    return NULL;
                }

                ShapeType_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->color() - (char *)sample);

                ShapeType_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->x() - (char *)sample);

                ShapeType_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->y() - (char *)sample);

                ShapeType_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->shapesize() - (char *)sample);

                ShapeType_g_sampleAccessInfo.memberAccessInfos = 
                ShapeType_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(ShapeType);

                    if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
                        ShapeType_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrUnsignedLong_MAX;
                    } else {
                        ShapeType_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ShapeType_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ShapeType_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ShapeType >;

                ShapeType_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &ShapeType_g_sampleAccessInfo;
            }

            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ShapeType_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ShapeType_g_typePlugin;
            }
        }; // native_type_code
        #endif

        const ::dds::core::xtypes::StructType& dynamic_type< ShapeType >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ShapeType >::get())));
        }

        #ifndef NDDS_STANDALONE_TYPE

        template<>
        struct native_type_code< ShapeTypeExtended > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode_Member ShapeTypeExtended_g_tc_members[2]=
                {

                    {
                        (char *)"fillKind",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"angle",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ShapeTypeExtended_g_tc =
                {{
                        DDS_TK_VALUE, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ShapeTypeExtended", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        ShapeTypeExtended_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ShapeTypeExtended*/

                if (is_initialized) {
                    return &ShapeTypeExtended_g_tc;
                }

                ShapeTypeExtended_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ShapeTypeExtended_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ShapeFillKind>::get().native();
                ShapeTypeExtended_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

                /* Initialize the values for member annotations. */
                ShapeTypeExtended_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ENUM;
                ShapeTypeExtended_g_tc_members[0]._annotations._defaultValue._u.enumerated_value = 0;

                ShapeTypeExtended_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                ShapeTypeExtended_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
                ShapeTypeExtended_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                ShapeTypeExtended_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                ShapeTypeExtended_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                ShapeTypeExtended_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

                ShapeTypeExtended_g_tc._data._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ShapeType >::get().native(); /* Base class */

                ShapeTypeExtended_g_tc._data._sampleAccessInfo = sample_access_info();
                ShapeTypeExtended_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized = RTI_TRUE;

                return &ShapeTypeExtended_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                ShapeTypeExtended *sample;

                static RTIXCdrMemberAccessInfo ShapeTypeExtended_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ShapeTypeExtended_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &ShapeTypeExtended_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ShapeTypeExtended);
                if (sample == NULL) {
                    return NULL;
                }

                ShapeTypeExtended_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->fillKind() - (char *)sample);

                ShapeTypeExtended_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->angle() - (char *)sample);

                ShapeTypeExtended_g_sampleAccessInfo.memberAccessInfos = 
                ShapeTypeExtended_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(ShapeTypeExtended);

                    if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
                        ShapeTypeExtended_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrUnsignedLong_MAX;
                    } else {
                        ShapeTypeExtended_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ShapeTypeExtended_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ShapeTypeExtended_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ShapeTypeExtended >;

                ShapeTypeExtended_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &ShapeTypeExtended_g_sampleAccessInfo;
            }

            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ShapeTypeExtended_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ShapeTypeExtended_g_typePlugin;
            }
        }; // native_type_code
        #endif

        const ::dds::core::xtypes::StructType& dynamic_type< ShapeTypeExtended >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ShapeTypeExtended >::get())));
        }

    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ShapeType >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ShapeTypePlugin_new,
                ShapeTypePlugin_delete);
        }

        std::vector<char>& topic_type_support< ShapeType >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ShapeType& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ShapeTypePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ShapeTypePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ShapeType >::from_cdr_buffer(ShapeType& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ShapeTypePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ShapeType from cdr buffer");
        }

        void topic_type_support< ShapeType >::reset_sample(ShapeType& sample) 
        {
            sample.color("");
            sample.x(0);
            sample.y(0);
            sample.shapesize(0);
        }

        void topic_type_support< ShapeType >::allocate_sample(ShapeType& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample); // [[maybe_unused]]

            ::rti::topic::allocate_sample(sample.color(),  -1, 128);
        }

        void topic_type_support< ShapeTypeExtended >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ShapeTypeExtendedPlugin_new,
                ShapeTypeExtendedPlugin_delete);
        }

        std::vector<char>& topic_type_support< ShapeTypeExtended >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ShapeTypeExtended& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ShapeTypeExtendedPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ShapeTypeExtendedPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ShapeTypeExtended >::from_cdr_buffer(ShapeTypeExtended& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ShapeTypeExtendedPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ShapeTypeExtended from cdr buffer");
        }

        void topic_type_support< ShapeTypeExtended >::reset_sample(ShapeTypeExtended& sample) 
        {
            // Initialize base
            topic_type_support< ShapeType >::reset_sample(sample);

            sample.fillKind(ShapeFillKind::SOLID_FILL);
            sample.angle(0.0f);
        }

        void topic_type_support< ShapeTypeExtended >::allocate_sample(ShapeTypeExtended& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample); // [[maybe_unused]]

            // Initialize base
            topic_type_support< ShapeType >::allocate_sample(sample, -1, -1);
            ::rti::topic::allocate_sample(sample.fillKind(),  -1, -1);
        }

    }
}  

