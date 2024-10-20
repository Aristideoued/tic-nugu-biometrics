#ifndef _BIOAPIERR_H_
#define _BIOAPIERR_H_


#define BIOAPI_FRAMEWORK_ERROR (0x00000000)
#define BIOAPI_BSP_ERROR       (0x01000000)
#define BIOAPI_UNIT_ERROR      (0x02000000)
#define BioAPIERR_IMPLEMENTATION_SPECIFIC                   (0x000000FF)
#define BioAPIERR_INTERNAL_ERROR                            (0x000101)
#define BioAPIERR_MEMORY_ERROR                              (0x000102)
#define BioAPIERR_INVALID_POINTER                           (0x000103)
#define BioAPIERR_INVALID_INPUT_POINTER                     (0x000104)
#define BioAPIERR_INVALID_OUTPUT_POINTER                    (0x000105)
#define BioAPIERR_FUNCTION_NOT_SUPPORTED                    (0x000106)
#define BioAPIERR_OS_ACCESS_DENIED                          (0x000107)
#define BioAPIERR_FUNCTION_FAILED                           (0x000108)
#define BioAPIERR_INVALID_UUID                              (0x000109)
#define BioAPIERR_INCOMPATIBLE_VERSION                      (0x00010a)
#define BioAPIERR_INVALID_DATA                              (0x00010b)
#define BioAPIERR_UNABLE_TO_CAPTURE                         (0x00010c)
#define BioAPIERR_TOO_MANY_HANDLES                          (0x00010d)
#define BioAPIERR_TIMEOUT_EXPIRED                           (0x00010e)
#define BioAPIERR_INVALID_BIR                               (0x00010f)
#define BioAPIERR_BIR_SIGNATURE_FAILURE                     (0x000110)
#define BioAPIERR_UNABLE_TO_STORE_PAYLOAD                   (0x000111)
#define BioAPIERR_NO_INPUT_BIRS                             (0x000112)
#define BioAPIERR_UNSUPPORTED_FORMAT                        (0x000113)
#define BioAPIERR_UNABLE_TO_IMPORT                          (0x000114)
#define BioAPIERR_INCONSISTENT_PURPOSE                      (0x000115)
#define BioAPIERR_BIR_NOT_FULLY_PROCESSED                   (0x000116)
#define BioAPIERR_PURPOSE_NOT_SUPPORTED                     (0x000117)
#define BioAPIERR_USER_CANCELLED                            (0x000118)
#define BioAPIERR_UNIT_IN_USE                               (0x000119)
#define BioAPIERR_INVALID_BSP_HANDLE                        (0x00011a)
#define BioAPIERR_FRAMEWORK_NOT_INITIALIZED                 (0x00011b)
#define BioAPIERR_INVALID_BIR_HANDLE                        (0x00011c)
#define BioAPIERR_CALIBRATION_NOT_SUCCESSFUL                (0x00011d)
#define BioAPIERR_PRESET_BIR_DOES_NOT_EXIST                 (0x00011e)
#define BioAPIERR_BIR_DECRYPTION_FAILURE                    (0x00011f)
#define BioAPIERR_COMPONENT_FILE_REF_NOT_FOUND              (0x000201)
#define BioAPIERR_BSP_LOAD_FAIL                             (0x000202)
#define BioAPIERR_BSP_NOT_LOADED                            (0x000203)
#define BioAPIERR_UNIT_NOT_INSERTED                         (0x000204)
#define BioAPIERR_INVALID_UNIT_ID                           (0x000205)
#define BioAPIERR_INVALID_CATEGORY                          (0x000206)
#define BioAPIERR_INVALID_DB_HANDLE                         (0x000300)
#define BioAPIERR_UNABLE_TO_OPEN_DATABASE                   (0x000301)
#define BioAPIERR_DATABASE_IS_LOCKED                        (0x000302)
#define BioAPIERR_DATABASE_DOES_NOT_EXIST                   (0x000303)
#define BioAPIERR_DATABASE_ALREADY_EXISTS                   (0x000304)
#define BioAPIERR_INVALID_DATABASE_NAME                     (0x000305)
#define BioAPIERR_RECORD_NOT_FOUND                          (0x000306)
#define BioAPIERR_MARKER_HANDLE_IS_INVALID                  (0x000307)
#define BioAPIERR_DATABASE_IS_OPEN                          (0x000308)
#define BioAPIERR_INVALID_ACCESS_REQUEST                    (0x000309)
#define BioAPIERR_END_OF_DATABASE                           (0x00030a)
#define BioAPIERR_UNABLE_TO_CREATE_DATABASE                 (0x00030b)
#define BioAPIERR_UNABLE_TO_CLOSE_DATABASE                  (0x00030c)
#define BioAPIERR_UNABLE_TO_DELETE_DATABASE                 (0x00030d)
#define BioAPIERR_DATABASE_IS_CORRUPT                       (0x00030e)
#define BioAPIERR_LOCATION_ERROR                            (0x000400)
#define BioAPIERR_OUT_OF_FRAME                              (0x000401)
#define BioAPIERR_INVALID_CROSSWISE_POSITION                (0x000402)
#define BioAPIERR_INVALID_LENGTHWISE_POSITION               (0x000403)
#define BioAPIERR_INVALID_DISTANCE                          (0x000404)
#define BioAPIERR_LOCATION_TOO_RIGHT                        (0x000405)
#define BioAPIERR_LOCATION_TOO_LEFT                         (0x000406)
#define BioAPIERR_LOCATION_TOO_HIGH                         (0x000407)
#define BioAPIERR_LOCATION_TOO_LOW                          (0x000408)
#define BioAPIERR_LOCATION_TOO_FAR                          (0x000409)
#define BioAPIERR_LOCATION_TOO_NEAR                         (0x00040a)
#define BioAPIERR_LOCATION_TOO_FORWARD                      (0x00040b)
#define BioAPIERR_LOCATION_TOO_BACKWARD                     (0x00040c)


#define BioAPIERR_QUALITY_ERROR                             (0x000501)


/*******************************************************************
The following errors are not specified by ISO/IEC 19794-1:2005 (BioAPI 2.0).
The Reference Implementation defines these errors as aliases to standard
BioAPI errors.  Future versions of the Reference Implementation may specify
different values for these errors.
/*******************************************************************/

#define BioAPIERR_COMPONENT_STATE_IS_CORRUPT            BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_ORPHANED_ATTACHMENT                   BioAPIERR_INVALID_BSP_HANDLE
#define BioAPIERR_UNABLE_TO_FREE_RESOURCES              BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_ACCESS_DENIED                         BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_UNABLE_TO_LOAD_CRDS                   BioAPIERR_FUNCTION_FAILED
#define BioAPIERR_UNIT_LIST_ACCESS_DENIED               BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_UNABLE_TO_ADD_UNIT                    BioAPIERR_MEMORY_ERROR
#define BioAPIERR_UNABLE_TO_REMOVE_UNIT                 BioAPIERR_INVALID_UNIT_ID
#define BioAPIERR_CRDS_ACCESS_DENIED                    BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_BSP_TABLE_ACCESS_DENIED               BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_ATTACHMENT_TABLE_ACCESS_DENIED        BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_BSP_ACCESS_DENIED                     BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_SESSION_ACCESS_DENIED                 BioAPIERR_INTERNAL_ERROR
#define BioAPIERR_FRAMEWORK_IS_IN_USE                   BioAPIERR_OS_ACCESS_DENIED

#endif /* _BIOAPIERR_H_ */
