

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ShapeType.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ShapeType_434673741_hpp
#define ShapeType_434673741_hpp

#include <iosfwd>

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/Optional.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/core/array.hpp"
#include "rti/core/BoundedSequence.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#include "rti/core/LongDouble.hpp"
#include "dds/core/External.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/topic/TopicTraits.hpp"

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

struct ShapeFillKind_def {
    enum type {
        SOLID_FILL,      
        TRANSPARENT_FILL,      
        HORIZONTAL_HATCH_FILL,      
        VERTICAL_HATCH_FILL     
    };
    static type get_default(){ return SOLID_FILL;}
};

typedef ::dds::core::safe_enum< ShapeFillKind_def > ShapeFillKind;
NDDSUSERDllExport std::ostream& operator << (std::ostream& o,const ShapeFillKind& sample);

class NDDSUSERDllExport ShapeType {
  public:
    ShapeType();

    ShapeType(
        const std::string& color,
        int32_t x,
        int32_t y,
        int32_t shapesize);

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    ShapeType (ShapeType&&) = default;
    ShapeType& operator=(ShapeType&&) = default;
    ShapeType& operator=(const ShapeType&) = default;
    ShapeType(const ShapeType&) = default;
    #else
    ShapeType(ShapeType&& other_) OMG_NOEXCEPT;  
    ShapeType& operator=(ShapeType&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 

    std::string& color() OMG_NOEXCEPT {
        return m_color_;
    }

    const std::string& color() const OMG_NOEXCEPT {
        return m_color_;
    }

    void color(const std::string& value) {
        m_color_ = value;
    }

    int32_t& x() OMG_NOEXCEPT {
        return m_x_;
    }

    const int32_t& x() const OMG_NOEXCEPT {
        return m_x_;
    }

    void x(int32_t value) {
        m_x_ = value;
    }

    int32_t& y() OMG_NOEXCEPT {
        return m_y_;
    }

    const int32_t& y() const OMG_NOEXCEPT {
        return m_y_;
    }

    void y(int32_t value) {
        m_y_ = value;
    }

    int32_t& shapesize() OMG_NOEXCEPT {
        return m_shapesize_;
    }

    const int32_t& shapesize() const OMG_NOEXCEPT {
        return m_shapesize_;
    }

    void shapesize(int32_t value) {
        m_shapesize_ = value;
    }

    bool operator == (const ShapeType& other_) const;
    bool operator != (const ShapeType& other_) const;

    void swap(ShapeType& other_) OMG_NOEXCEPT ;

  private:

    std::string m_color_;
    int32_t m_x_;
    int32_t m_y_;
    int32_t m_shapesize_;

};

inline void swap(ShapeType& a, ShapeType& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}

NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ShapeType& sample);

class NDDSUSERDllExport ShapeTypeExtended
: public ShapeType {
  public:
    ShapeTypeExtended();

    ShapeTypeExtended(
        const std::string& color,
        int32_t x,
        int32_t y,
        int32_t shapesize,
        const ShapeFillKind& fillKind,
        float angle);

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    ShapeTypeExtended (ShapeTypeExtended&&) = default;
    ShapeTypeExtended& operator=(ShapeTypeExtended&&) = default;
    ShapeTypeExtended& operator=(const ShapeTypeExtended&) = default;
    ShapeTypeExtended(const ShapeTypeExtended&) = default;
    #else
    ShapeTypeExtended(ShapeTypeExtended&& other_) OMG_NOEXCEPT;  
    ShapeTypeExtended& operator=(ShapeTypeExtended&&  other_) OMG_NOEXCEPT;
    #endif
    #endif 

    ShapeFillKind& fillKind() OMG_NOEXCEPT {
        return m_fillKind_;
    }

    const ShapeFillKind& fillKind() const OMG_NOEXCEPT {
        return m_fillKind_;
    }

    void fillKind(const ShapeFillKind& value) {
        m_fillKind_ = value;
    }

    float& angle() OMG_NOEXCEPT {
        return m_angle_;
    }

    const float& angle() const OMG_NOEXCEPT {
        return m_angle_;
    }

    void angle(float value) {
        m_angle_ = value;
    }

    bool operator == (const ShapeTypeExtended& other_) const;
    bool operator != (const ShapeTypeExtended& other_) const;

    void swap(ShapeTypeExtended& other_) OMG_NOEXCEPT ;

  private:

    ShapeFillKind m_fillKind_;
    float m_angle_;

};

inline void swap(ShapeTypeExtended& a, ShapeTypeExtended& b)  OMG_NOEXCEPT 
{
    a.swap(b);
}

NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ShapeTypeExtended& sample);

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< ShapeType > {
            NDDSUSERDllExport static std::string value() {
                return "ShapeType";
            }
        };

        template<>
        struct is_topic_type< ShapeType > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ShapeType > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ShapeType& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(ShapeType& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(ShapeType& sample);

            NDDSUSERDllExport 
            static void allocate_sample(ShapeType& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };

        template<>
        struct topic_type_name< ShapeTypeExtended > {
            NDDSUSERDllExport static std::string value() {
                return "ShapeTypeExtended";
            }
        };

        template<>
        struct is_topic_type< ShapeTypeExtended > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ShapeTypeExtended > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ShapeTypeExtended& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(ShapeTypeExtended& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(ShapeTypeExtended& sample);

            NDDSUSERDllExport 
            static void allocate_sample(ShapeTypeExtended& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };

    }
}

namespace rti { 
    namespace topic {
        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< ShapeFillKind > {
            typedef ::dds::core::xtypes::EnumType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::EnumType& get();
        };
        #endif

        template <>
        struct extensibility< ShapeFillKind > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;                
        };

        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< ShapeType > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif

        template <>
        struct extensibility< ShapeType > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;                
        };

        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< ShapeTypeExtended > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif

        template <>
        struct extensibility< ShapeTypeExtended > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;                
        };

    }
}

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // ShapeType_434673741_hpp

