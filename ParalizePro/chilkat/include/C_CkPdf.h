// This is a generated source file for Chilkat version 9.5.0.76
#ifndef _C_CkPdf_H
#define _C_CkPdf_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkPdf CkPdf_Create(void);
CK_VISIBLE_PUBLIC void CkPdf_Dispose(HCkPdf handle);
CK_VISIBLE_PUBLIC void CkPdf_getDebugLogFilePath(HCkPdf cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkPdf_putDebugLogFilePath(HCkPdf cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkPdf_debugLogFilePath(HCkPdf cHandle);
CK_VISIBLE_PUBLIC int CkPdf_getI(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_putI(HCkPdf cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkPdf_getLastErrorHtml(HCkPdf cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPdf_lastErrorHtml(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_getLastErrorText(HCkPdf cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPdf_lastErrorText(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_getLastErrorXml(HCkPdf cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPdf_lastErrorXml(HCkPdf cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdf_getLastMethodSuccess(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_putLastMethodSuccess(HCkPdf cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkPdf_getNumPages(HCkPdf cHandle);
CK_VISIBLE_PUBLIC int CkPdf_getNumSignatures(HCkPdf cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdf_getUtf8(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_putUtf8(HCkPdf cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkPdf_getVerboseLogging(HCkPdf cHandle);
CK_VISIBLE_PUBLIC void CkPdf_putVerboseLogging(HCkPdf cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkPdf_getVersion(HCkPdf cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkPdf_version(HCkPdf cHandle);
CK_VISIBLE_PUBLIC BOOL CkPdf_ExtractPageTextSa(HCkPdf cHandle, int pageNum, HCkStringArray sa);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetObjectInfo(HCkPdf cHandle, const char *pdfPath, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPdf_getObjectInfo(HCkPdf cHandle, const char *pdfPath);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetPageContents(HCkPdf cHandle, int pageNum, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPdf_getPageContents(HCkPdf cHandle, int pageNum);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetSignatureSigningTime(HCkPdf cHandle, int index, HCkDateTime dt);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetSignerCert(HCkPdf cHandle, int index, HCkCert cert);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetSignerName(HCkPdf cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPdf_getSignerName(HCkPdf cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdf_GetSigningReason(HCkPdf cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkPdf_getSigningReason(HCkPdf cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdf_HasSignatureSigningTime(HCkPdf cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkPdf_Open(HCkPdf cHandle, const char *filePath);
CK_VISIBLE_PUBLIC BOOL CkPdf_OpenBd(HCkPdf cHandle, HCkBinData pdfData);
CK_VISIBLE_PUBLIC BOOL CkPdf_SaveLastError(HCkPdf cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkPdf_VerifySignatures(HCkPdf cHandle);
#endif
