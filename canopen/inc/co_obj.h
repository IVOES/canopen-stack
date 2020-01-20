/******************************************************************************
   Copyright 2020 Embedded Office GmbH & Co. KG

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************/

#ifndef CO_OBJ_H_
#define CO_OBJ_H_

/******************************************************************************
* INCLUDES
******************************************************************************/

#include "co_types.h"
#include "co_cfg.h"

/******************************************************************************
* DEFINES
******************************************************************************/

#define CO_OBJ____R_     0x01    /*!< Read Only                              */
#define CO_OBJ_____W     0x02    /*!< Write Only                             */
#define CO_OBJ____RW     0x03    /*!< Read/Write                             */
#define CO_OBJ___P__     0x04    /*!< PDO Map                                */
#define CO_OBJ___PR_     0x05    /*!< Read Only, PDO Map                     */
#define CO_OBJ___P_W     0x06    /*!< Write Only, PDO Map                    */
#define CO_OBJ___PRW     0x07    /*!< Read/Write, PDO Map                    */
#define CO_OBJ__N___     0x40    /*!< Consider Node-Id                       */
#define CO_OBJ__N_R_     0x41    /*!< Read Only, + Node-Id                   */
#define CO_OBJ__N__W     0x42    /*!< Write Only, - Node-Id                  */
#define CO_OBJ__N_RW     0x43    /*!< Read/Write, +/- Node-Id                */
#define CO_OBJ__NPR_     0x45    /*!< Read Only, PDO Map, + Node-Id          */
#define CO_OBJ__NP_W     0x46    /*!< Write Only, PDO Map, - Node-Id         */
#define CO_OBJ__NPRW     0x47    /*!< Read/Write, PDO Map, +/- Node-Id       */
#define CO_OBJ_D____     0x80    /*!< Direct Access (Ptr = Value)            */
#define CO_OBJ_D__R_     0x81    /*!< Read Only, Direct Access               */
#define CO_OBJ_D___W     0x82    /*!< Write Only, Direct Access              */
#define CO_OBJ_D__RW     0x83    /*!< Read/Write, Direct Access              */
#define CO_OBJ_DN_R_     0xC1    /*!< Read Only, + Node-Id, Direct Access    */
#define CO_OBJ_DN__W     0xC2    /*!< Write Only, - Node-Id, Direct Access   */
#define CO_OBJ_DN_RW     0xC3    /*!< Read/Write, +/- Node-Id, Direct Access */

#define CO_OBJ_SGN       0x08    /*!< Signed number                          */
#define CO_OBJ_SZ1       0x00    /*!< Size 2^0 = 1 Byte                      */
#define CO_OBJ_SZ2       0x10    /*!< Size 2^1 = 2 Byte                      */
#define CO_OBJ_SZ4       0x20    /*!< Size 2^2 = 4 Byte                      */
#define CO_OBJ_SZ8       0x30    /*!< Size 2^3 = 8 Byte                      */

#define CO_OBJ_FLG_MSK   0xC7    /*!< Mask for flags                         */
#define CO_OBJ_SZ_MSK    0x30    /*!< Mask for fixed object size             */
#define CO_OBJ_FMT_MSK   0x38    /*!< Mask for format                        */

#define CO_UNSIGNED8     CO_OBJ_SZ1               /*!< Datatype: UNSIGNED8   */
#define CO_UNSIGNED16    CO_OBJ_SZ2               /*!< Datatype: UNSIGNED16  */
#define CO_UNSIGNED32    CO_OBJ_SZ4               /*!< Datatype: UNSIGNED32  */
#define CO_UNSIGNED64    CO_OBJ_SZ8               /*!< Datatype: UNSIGNED64  */
#define CO_SIGNED8       (CO_OBJ_SGN|CO_OBJ_SZ1)  /*!< Datatype: SIGNED8     */
#define CO_SIGNED16      (CO_OBJ_SGN|CO_OBJ_SZ2)  /*!< Datatype: SIGNED16    */
#define CO_SIGNED32      (CO_OBJ_SGN|CO_OBJ_SZ4)  /*!< Datatype: SIGNED32    */
#define CO_FLOAT         0                        /*!< Datatype: FLOAT       */
#define CO_DOMAIN        0                        /*!< Datatype: DOMAIN      */
#define CO_STRING        0                        /*!< Datatype: STRING      */

#define CO_BYTE          1                /*!< Number of bytes for a byte    */
#define CO_WORD          2                /*!< Number of bytes for a word    */
#define CO_LONG          4                /*!< Number of bytes for a long    */

#define CO_CTRL_SET_OFF  1       /*!< Set read/write offset for next access  */

/*! \brief OBJECT DIRECTORY ENDMARKER
*
*    This define may be used in object directory definitions. It marks the
*    first unused object entry.
*/
#define CO_OBJ_DIR_ENDMARK   { (uint32_t)0, (CO_OBJ_TYPE *)0, (uint32_t)0 }

#define CO_TSTRING    ((CO_OBJ_TYPE *)&COTString)   /*!< Object Type String  */
#define CO_TDOMAIN    ((CO_OBJ_TYPE *)&COTDomain)   /*!< Object Type Domain  */
    
/******************************************************************************
* PUBLIC MACROS
******************************************************************************/

/*! \brief OBJECT KEY
*
*    This macro helps to build the CANopen object member variable 'key'.
*    This variable is used to hold the unique address of the object entry
*    with index:subindex. Furthermore the lower 8bits of the key are used
*    to describe the way of accessing this object entry.
*
* \param idx
*    CANopen object index [0x0000..0xFFFF]
*
* \param sub
*    CANopen object subindex [0x00..0xFF]
*
* \param flags
*    The additional object property flags
*/
#define CO_KEY(idx,sub,flags)            \
    ( (uint32_t)((  idx) & 0xFFFF)<<16 | \
      (uint32_t)((  sub) &   0xFF)<< 8 | \
      (uint32_t)((flags) &   0xFF)     )

/*! \brief OBJECT DEVICE
*
*    This macro helps to build the CANopen object member device identifier.
*    This identifier is used to search the unique address of the object
*    entry (index:subindex).
*
* \param idx
*    CANopen object index [0x0000..0xFFFF]
*
* \param sub
*    CANopen object subindex [0x00..0xFF]
*/
#define CO_DEV(idx,sub)                \
    ( (uint32_t)((idx) & 0xFFFF)<<16 | \
      (uint32_t)((sub) &   0xFF)<<8  )

/*! \brief OBJECT MAPPING LINK
*
*    This macro helps to build the CANopen object entry for a PDO mapping.
*    This entry is used to specify the linked signal within a PDO.
*
* \param idx
*    CANopen object index [0x0000..0xFFFF]
*
* \param sub
*    CANopen object subindex [0x00..0xFF]
*
* \param bit
*    Length of mapped signal in bits [8,16 or 32]
*/
#define CO_LINK(idx,sub,bit)           \
    ( (uint32_t)((idx) & 0xFFFF)<<16 | \
      (uint32_t)((sub) &   0xFF)<<8  | \
      (uint32_t)((bit) &   0xFF)     )

/*! \brief EXTRACT DEVICE
*
*    This macro helps to extract the index and subindex out of the CANopen
*    object entry member 'key'.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_GET_DEV(key)    (uint32_t)(((key) & 0xFFFFFF00))

/*! \brief EXTRACT SUBINDEX
*
*    This macro helps to extract the subindex out of the CANopen object
*    entry member 'key'.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_GET_SUB(key)    (uint8_t)(((key) & 0x0000FF00) >> 8)

/*! \brief EXTRACT INDEX
*
*    This macro helps to extract the index out of the CANopen object entry
*    member 'key'.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_GET_IDX(key)    (uint16_t)((key) >> 16)

/*! \brief EXTRACT SIZE
*
*    This macro helps to extract the object entry size in bytes out of the
*    CANopen object entry member 'key'. If this result is 0, the size must
*    be calculated with the function Size(), referenced in the linked type
*    structure.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_GET_SIZE(key)    (uint32_t)(1L << (((key) & CO_OBJ_SZ_MSK) >> 4))

/*! \brief CHECK IF OBJECT IS PDO MAPPABLE
*
*    This macro helps to determine, if the object entry is PDO mappable.
*    The macro masks the corresponding bit from the flags bitfield.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_IS_PDOMAP(key)    (uint32_t)(key & CO_OBJ___P__)

/*! \brief CHECK IF OBJECT DEPENDS ON NODE-ID
*
*    This macro helps to determine, if the object entry value depends on
*    the node-ID. The macro masks the corresponding bit from the flags
*    bit field.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_IS_NODEID(key)    (uint32_t)(key & CO_OBJ__N___)

/*! \brief CHECK IF OBJECT IS A DIRECT
*
*    This macro helps to determine, if the object entry value is a direct
*    value. The macro masks the corresponding bit from the flags bitfield.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_IS_DIRECT(key)    (uint32_t)(key & CO_OBJ_D____)

/*! \brief CHECK IF OBJECT IS READABLE
*
*    This macro helps to determine, if the object entry value is readable.
*    The macro masks the corresponding bit from the flags bitfield.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_IS_READ(key)    (uint32_t)(key & CO_OBJ____R_)

/*! \brief CHECK IF OBJECT IS WRITEABLE
*
*    This macro helps to determine, if the object entry value is writeable.
*    The macro masks the corresponding bit from the flags bitfield.
*
* \param key
*    CANopen object member variable 'key'.
*/
#define CO_IS_WRITE(key)    (uint32_t)(key & CO_OBJ_____W)

/******************************************************************************
* PUBLIC TYPES
******************************************************************************/

struct CO_OBJ_TYPE_T;            /* Declaration of object type structure     */
struct CO_DIR_T;                 /* Declaration of object directory structure*/

/*! \brief OBJECT ENTRY
*
*    This structure holds all data, needed for managing a single object
*    entry.
*/
typedef struct CO_OBJ_T {
    uint32_t              Key;   /*!< 16Bit Index, 8Bit Subindex, 8Bit Flags */
                                 /*   - 0: 1=rd access allowed               */
                                 /*   - 1: 1=wr access allowed               */
                                 /*   - 2: 1=pdo mappable                    */
                                 /*   - 3: 1=signed value                    */
                                 /*   - 4: |- valid bytes in 2^n; used if    */
                                 /*   - 5: |  Type=0, or Type->Size ptr=0    */
                                 /*   - 6: 1=+/- node-id on read/write       */
                                 /*   - 7: 1=direct (ptr is value if Type=0) */
    struct CO_OBJ_TYPE_T *Type;  /*!< ==0: value access via Data-Ptr,        */
                                 /*   !=0: access via type structure         */
    uint32_t              Data;  /*!< Address of value or data structure     */
                                 /*   or data value for direct access        */
} CO_OBJ;

/*!< Size type function prototype */
typedef uint32_t (*CO_OBJ_SIZE_FUNC) (CO_OBJ *, uint32_t);
/*!< Control type function prototype */
typedef int16_t  (*CO_OBJ_CTRL_FUNC) (CO_OBJ *, uint16_t, uint32_t);
/*!< Read type function prototype */
typedef int16_t  (*CO_OBJ_READ_FUNC) (CO_OBJ *, void*, uint32_t);
/*!< Write type function prototype */
typedef int16_t  (*CO_OBJ_WRITE_FUNC)(CO_OBJ *, void*, uint32_t);

/*! \brief OBJECT TYPE
*
*    This structure holds all data, needed for managing a special object
*    entry type.
*/
typedef struct CO_OBJ_TYPE_T {
    struct CO_DIR_T   *Dir;            /*!< Link to parent object directory  */
    uint32_t           Offset;         /*!< Offset within the data memory    */
    CO_OBJ_SIZE_FUNC   Size;           /*!< Get size of type function        */
    CO_OBJ_CTRL_FUNC   Ctrl;           /*!< Special type control function    */
    CO_OBJ_READ_FUNC   Read;           /*!< Read function                    */
    CO_OBJ_WRITE_FUNC  Write;          /*!< Write function                   */

} CO_OBJ_TYPE;

/*! \brief DOMAIN MANAGEMENT STRUCTURE
*
*    This structure holds all data, which are needed for the domain object
*    management within the object directory.
*/
typedef struct CO_DOM_T {
    uint32_t  Size;                    /*!< Domain size information          */
    uint8_t  *Start;                   /*!< Domain start address             */

} CO_DOM;

/******************************************************************************
* PUBLIC CONSTANTS
******************************************************************************/

/*! \brief OBJECT TYPE STRING
*
*    This type is responsible for the access to unlimited string constants.
*    It is assumed, that the strings are declared in nonvolatile memory
*    (e.g. FLASH) and the starting address is stored in the object entry
*    member 'Data'.
*
* \note
*    If the object entry is marked to be read-/write-able, the write access
*    to the object entry will change the start address of the string - not
*    the string itself. If writing the string itself is needed, another
*    (user-)type must be defined. The write function must be adapted
*    with the needed memory handling. The other functions may be reused.
*/
extern const CO_OBJ_TYPE COTString;

/*! \brief OBJECT TYPE DOMAIN
*
*    This type is responsible for the access to domain memory areas. It is
*    assumed, that the memory is declared in random accessible memory
*    (e.g. RAM, FLASH, etc..).
*
* \note
*    This exemplary implementation is usable for reading and writing in
*    direct accessible memory (e.g. RAM). The reading from FLASH memory is
*    no problem, but for the write access to FLASH memory, there should be
*    a special DOMAIN implementation for this media.
*/
extern const CO_OBJ_TYPE COTDomain;

/******************************************************************************
* PUBLIC FUNCTIONS
******************************************************************************/

/*! \brief  GET SIZE OF OBJECT ENTRY
*
*    This function returns the size of the given object directory entry.
*
* \param obj
*    pointer to the CANopen directory entry
*
* \param width
*    Expected object size in byte (or 0 if unknown)
*
* \retval  >0    Object entry size in bytes
* \retval  =0    An error is detected
*/
uint32_t COObjGetSize(CO_OBJ *obj, uint32_t width);

/*! \brief  READ VALUE FROM OBJECT ENTRY
*
*    This function reads a value from the given object directory entry.
*
* \param obj
*    pointer to the CANopen directory entry
*
* \param value
*    pointer to the result memory
*
* \param width
*    width of read value (must be 1, 2 or 4 and reflecting the width
*    of the referenced variable with given parameter pointer: value)
*
* \param nodeid
*    device nodeid (only used in case of node-id dependent value)
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjRdValue(CO_OBJ *obj, void *value, uint8_t width, uint8_t nodeid);

/*! \brief  WRITE VALUE TO OBJECT ENTRY
*
*    This function writes a value to the given object directory entry.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param value
*    pointer to the source memory
*
* \param width
*    width of write value (must be 1, 2 or 4 and reflecting the width
*    of the referenced variable with given parameter pointer: value)
*
* \param nodeid
*    device nodeid (only used in case of node-id dependent value)
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjWrValue(CO_OBJ *obj, void *value, uint8_t width, uint8_t nodeid);

/*! \brief  START READ BUFFER FROM OBJECT ENTRY
*
*    This function starts the read operation at the beginning of the byte
*    stream from the given object directory entry into the given destination
*    buffer.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param buffer
*    pointer to the destination buffer
*
* \param len
*    length of destination buffer
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjRdBufStart(CO_OBJ *obj, uint8_t *buffer, uint32_t len);

/*! \brief  CONTINUE READ BUFFER FROM OBJECT ENTRY
*
*    This function continues the read operation at the current offset of
*    the byte stream from the given object directory entry into the given
*    destination buffer.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param buffer
*    pointer to the destination buffer
*
* \param len
*    length of destination buffer
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjRdBufCont(CO_OBJ *obj, uint8_t *buffer, uint32_t len);

/*! \brief  START WRITE BUFFER TO OBJECT ENTRY
*
*    This function starts the write operation at the beginning of the
*    given object directory entry from the given source buffer.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param buffer
*    pointer to the source buffer
*
* \param len
*    length of source buffer
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjWrBufStart(CO_OBJ *obj, uint8_t *buffer, uint32_t len);

/*! \brief  CONTINUE WRITE BUFFER TO OBJECT ENTRY
*
*    This function continues the write operation at the current offset of
*    the byte stream from the given source buffer to the object directory
*    entry.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param buffer
*    pointer to the source buffer
*
* \param len
*    length of source buffer
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjWrBufCont(CO_OBJ *obj, uint8_t *buffer, uint32_t len);

/******************************************************************************
* PRIVATE FUNCTIONS
******************************************************************************/

/*! \brief  INIT OBJECT ENTRY
*
*    This function (re-)initializes an object entry element.
*
* \param obj
*    pointer to the object entry
*/
void COObjInit(CO_OBJ *obj);

/*! \brief  COMPARE GIVEN VALUE WITH OBJECT ENTRY VALUE
*
*    This function compares the given value with the currently stored value
*    within the object directory.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param val
*    new value, (casted to 32bit value)
*
* \retval  =0    new value is equal to stored value
* \retval  >0    new value is not equal to stored value
* \retval  <0    an error is detected within this function
*/
int16_t COObjCmp(CO_OBJ *obj, void *val);

/*! \brief  DIRECT READ FROM DATA POINTER
*
*    This function reads the value of the entry directly from the data
*    pointer. This function checks the internal flags and reacts as
*    configured: reading the pointer address as value, or use the address
*    and get the value from that address.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param val
*    pointer to the result memory
*
* \param len
*    length of value in bytes
*
* \retval    =CO_ERR_NONE    Successfully operation
* \retval   !=CO_ERR_NONE    An error is detected
*/
int16_t COObjRdDirect(CO_OBJ *obj, void *val, uint32_t len);

/*! \brief  DIRECT WRITE TO DATA POINTER
*
*    This function writes the value to the entry directly to the data pointer.
*    This function checks the internal flags and reacts as configured: writing
*    the value to the pointer address, or use the address and write the value
*    to that address.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param val
*    pointer to the source memory
*
* \param len
*    length of value in bytes
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjWrDirect(CO_OBJ *obj, void *val, uint32_t len);

/*! \brief  READ WITH TYPE FUNCTIONS
*
*    This function reads the value of the entry directly with the linked
*    type-functions.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param dst
*    pointer to the result memory
*
* \param len
*    length of value in bytes
*
* \param off
*    set this offset, before reading
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COObjRdType(CO_OBJ *obj, void *dst, uint32_t len, uint32_t off);

/*! \brief  WRITE WITH TYPE FUNCTIONS
*
*    This function writes the value of the entry directly with the linked
*    type-functions.
*
* \param obj
*    pointer to the CANopen object directory entry
*
* \param src
*    pointer to the source memory
*
* \param len
*    length of value in bytes
*
* \param off
*    set this offset, before writing
*
* \retval    =CO_ERR_NONE    Successfully operation
* \retval   !=CO_ERR_NONE    An error is detected
*/
int16_t COObjWrType(CO_OBJ *obj, void *dst, uint32_t len, uint32_t off);

/*! \brief STRING OBJECT SIZE
*
*    This function is responsible to calculate and return the size of the
*    string, which starts at the object entry member 'Data'. The string
*    length calculation stopps at the end-of-string character ('\0') and
*    returns the number of characters without the final 0.
*
* \param obj
*    String object entry reference
*
* \param width
*    Requested string size (or 0 if unknown)
*
* \return
*    Number of character in the string, counting without the end of string
*    mark.
*/
uint32_t COTypeStringSize(CO_OBJ *obj, uint32_t width);

/*! \brief STRING OBJECT ACCESS CONTROL
*
*    This function is responsible to perform special control operations on
*    the object entry. This control function supports the function(s):
*
*    - CO_CTRL_SET_OFF: set the working offset to the given value in para
*                       for subsequent read function calls.
*
* \param obj
*    String object entry reference
*
* \param func
*    Control function code
*
* \param para
*    Control function parameter
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COTypeStringCtrl(CO_OBJ *obj, uint16_t func, uint32_t para);

/*! \brief STRING OBJECT READ ACCESS
*
*    This function is responsible to copy the string characters from the
*    object entry into the given buffer memory.
*
* \param obj
*    String object entry reference
*
* \param buf
*    Pointer to buffer memory
*
* \param len
*    Length of buffer memory
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COTypeStringRead(CO_OBJ *obj, void *buf, uint32_t len);

/*! \brief DOMAIN OBJECT SIZE
*
*    This function is responsible to return the size of the Domain.
*
* \param obj
*    Domain object entry reference
*
* \param width
*    Requested Domain size (or 0 if unknown)
*
* \return
*    Size in bytes of the domain.
*/
uint32_t COTypeDomainSize(CO_OBJ *obj, uint32_t width);

/*! \brief DOMAIN OBJECT ACCESS CONTROL
*
*    This function is responsible to perform special control operations on
*    the object entry. This control function supports the function(s):
*
*    - CO_CTRL_SET_OFF: set the working offset to the given value in para
*                       for subsequent read function calls.
*
* \param obj
*    Domain object entry reference
*
* \param func
*    Control function code
*
* \param para
*    Control function parameter
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COTypeDomainCtrl(CO_OBJ *obj, uint16_t func, uint32_t para);

/*! \brief DOMAIN OBJECT READ ACCESS
*
*    This function is responsible to copy the domain memory from the
*    object entry into the given buffer memory.
*
* \param obj
*    Domain object entry reference
*
* \param buf
*    Pointer to buffer memory
*
* \param len
*    Length of buffer memory
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COTypeDomainRead(CO_OBJ *obj, void *buf, uint32_t len);

/*! \brief DOMAIN OBJECT WRITE ACCESS
*
*    This function is responsible to copy the given buffer memory into the
*    object entry domain memory.
*
* \param obj
*    Domain object entry reference
*
* \param buf
*    Pointer to buffer memory
*
* \param len
*    Length of buffer memory
*
* \retval   =CO_ERR_NONE    Successfully operation
* \retval  !=CO_ERR_NONE    An error is detected
*/
int16_t COTypeDomainWrite(CO_OBJ *obj, void *buf, uint32_t len);

#endif  /* #ifndef CO_OBJ_H_ */
