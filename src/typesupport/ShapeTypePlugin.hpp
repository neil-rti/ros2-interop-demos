

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ShapeType.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ShapeTypePlugin_434673741_h
#define ShapeTypePlugin_434673741_h

#include "ShapeType.hpp"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern unsigned int 
ShapeFillKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern unsigned int 
ShapeFillKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
ShapeFillKindPlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* ----------------------------------------------------------------------------
Support functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
ShapeFillKindPluginSupport_print_data(
    const ShapeFillKind *sample, const char *desc, int indent_level);

/* The type used to store keys for instances of type struct
* AnotherSimple.
*
* By default, this type is struct ShapeType
* itself. However, if for some reason this choice is not practical for your
* system (e.g. if sizeof(struct ShapeType)
* is very large), you may redefine this typedef in terms of another type of
* your choosing. HOWEVER, if you define the KeyHolder type to be something
* other than struct AnotherSimple, the
* following restriction applies: the key of struct
* ShapeType must consist of a
* single field of your redefined KeyHolder type and that field must be the
* first field in struct ShapeType.
*/
typedef  class ShapeType ShapeTypeKeyHolder;

#define ShapeTypePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

#define ShapeTypePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define ShapeTypePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

#define ShapeTypePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define ShapeTypePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

#define ShapeTypePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define ShapeTypePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern ShapeType*
ShapeTypePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern ShapeType*
ShapeTypePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ShapeType*
ShapeTypePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
ShapeTypePluginSupport_copy_data(
    ShapeType *out,
    const ShapeType *in);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_destroy_data_w_params(
    ShapeType *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_destroy_data_ex(
    ShapeType *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_destroy_data(
    ShapeType *sample);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_print_data(
    const ShapeType *sample,
    const char *desc,
    unsigned int indent);

NDDSUSERDllExport extern ShapeType*
ShapeTypePluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ShapeType*
ShapeTypePluginSupport_create_key(void);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_destroy_key_ex(
    ShapeTypeKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ShapeTypePluginSupport_destroy_key(
    ShapeTypeKeyHolder *key);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
ShapeTypePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
ShapeTypePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
ShapeTypePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
ShapeTypePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
ShapeTypePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ShapeType *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ShapeType *out,
    const ShapeType *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool
ShapeTypePlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const ShapeType *sample,
    ::dds::core::policy::DataRepresentationId representation
    = ::dds::core::policy::DataRepresentation::xcdr()); 

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ShapeType **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
ShapeTypePlugin_deserialize_from_cdr_buffer(
    ShapeType *sample,
    const char * buffer,
    unsigned int length);    

NDDSUSERDllExport extern unsigned int 
ShapeTypePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
ShapeTypePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
ShapeTypePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
ShapeTypePlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ShapeType ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeKeyHolder *key, 
    const ShapeType *instance);

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ShapeType *instance, 
    const ShapeTypeKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ShapeType *instance,
    RTIEncapsulationId encapsulationId);

NDDSUSERDllExport extern RTIBool 
ShapeTypePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
ShapeTypePlugin_new(void);

NDDSUSERDllExport extern void
ShapeTypePlugin_delete(struct PRESTypePlugin *);

/* The type used to store keys for instances of type struct
* AnotherSimple.
*
* By default, this type is struct ShapeTypeExtended
* itself. However, if for some reason this choice is not practical for your
* system (e.g. if sizeof(struct ShapeTypeExtended)
* is very large), you may redefine this typedef in terms of another type of
* your choosing. HOWEVER, if you define the KeyHolder type to be something
* other than struct AnotherSimple, the
* following restriction applies: the key of struct
* ShapeTypeExtended must consist of a
* single field of your redefined KeyHolder type and that field must be the
* first field in struct ShapeTypeExtended.
*/
typedef  class ShapeTypeExtended ShapeTypeExtendedKeyHolder;

#define ShapeTypeExtendedPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

#define ShapeTypeExtendedPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define ShapeTypeExtendedPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

#define ShapeTypeExtendedPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define ShapeTypeExtendedPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

#define ShapeTypeExtendedPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define ShapeTypeExtendedPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern ShapeTypeExtended*
ShapeTypeExtendedPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern ShapeTypeExtended*
ShapeTypeExtendedPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ShapeTypeExtended*
ShapeTypeExtendedPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPluginSupport_copy_data(
    ShapeTypeExtended *out,
    const ShapeTypeExtended *in);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_destroy_data_w_params(
    ShapeTypeExtended *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_destroy_data_ex(
    ShapeTypeExtended *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_destroy_data(
    ShapeTypeExtended *sample);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_print_data(
    const ShapeTypeExtended *sample,
    const char *desc,
    unsigned int indent);

NDDSUSERDllExport extern ShapeTypeExtended*
ShapeTypeExtendedPluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ShapeTypeExtended*
ShapeTypeExtendedPluginSupport_create_key(void);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_destroy_key_ex(
    ShapeTypeExtendedKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPluginSupport_destroy_key(
    ShapeTypeExtendedKeyHolder *key);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
ShapeTypeExtendedPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
ShapeTypeExtendedPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
ShapeTypeExtendedPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
ShapeTypeExtendedPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtended *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtended *out,
    const ShapeTypeExtended *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool
ShapeTypeExtendedPlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const ShapeTypeExtended *sample,
    ::dds::core::policy::DataRepresentationId representation
    = ::dds::core::policy::DataRepresentation::xcdr()); 

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtended **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
ShapeTypeExtendedPlugin_deserialize_from_cdr_buffer(
    ShapeTypeExtended *sample,
    const char * buffer,
    unsigned int length);    

NDDSUSERDllExport extern unsigned int 
ShapeTypeExtendedPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
ShapeTypeExtendedPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
ShapeTypeExtendedPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
ShapeTypeExtendedPlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtended ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtendedKeyHolder *key, 
    const ShapeTypeExtended *instance);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ShapeTypeExtended *instance, 
    const ShapeTypeExtendedKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ShapeTypeExtended *instance,
    RTIEncapsulationId encapsulationId);

NDDSUSERDllExport extern RTIBool 
ShapeTypeExtendedPlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
ShapeTypeExtendedPlugin_new(void);

NDDSUSERDllExport extern void
ShapeTypeExtendedPlugin_delete(struct PRESTypePlugin *);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ShapeTypePlugin_434673741_h */

