// CkPdfW.h: interface for the CkPdfW class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat 9.5.0.76

#ifndef _CkPdfW_H
#define _CkPdfW_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkWideCharBase.h"

class CkStringArrayW;
class CkDateTimeW;
class CkCertW;
class CkBinDataW;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkPdfW
class CK_VISIBLE_PUBLIC CkPdfW  : public CkWideCharBase
{
    private:
	

	// Don't allow assignment or copying these objects.
	CkPdfW(const CkPdfW &);
	CkPdfW &operator=(const CkPdfW &);

    public:
	CkPdfW(void);
	virtual ~CkPdfW(void);

	static CkPdfW *createNew(void);
	

	
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The value of the "i" index to be used when evaluating a PDF path.
	int get_I(void);
	// The value of the "i" index to be used when evaluating a PDF path.
	void put_I(int newVal);

	// The number of pages in the currently open PDF.
	int get_NumPages(void);

	// The number of digital signatures present in the currently open PDF.
	int get_NumSignatures(void);



	// ----------------------
	// Methods
	// ----------------------
	// Extract the text from a page, where the first pageNum is 0. The extracted text is
	// deposited into sa. Each entry added to sa corresponds to the contents of a
	// single "marked content" section on the page (typically a paragraph).
	bool ExtractPageTextSa(int pageNum, CkStringArrayW &sa);

	// Returns text describing the object contained within the PDF at the pdfPath.
	bool GetObjectInfo(const wchar_t *pdfPath, CkString &outStr);
	// Returns text describing the object contained within the PDF at the pdfPath.
	const wchar_t *getObjectInfo(const wchar_t *pdfPath);
	// Returns text describing the object contained within the PDF at the pdfPath.
	const wchar_t *objectInfo(const wchar_t *pdfPath);

	// Returns the a page's /Contents.
	bool GetPageContents(int pageNum, CkString &outStr);
	// Returns the a page's /Contents.
	const wchar_t *getPageContents(int pageNum);
	// Returns the a page's /Contents.
	const wchar_t *pageContents(int pageNum);

	// Gets the signing time for the Nth signature. The dt is set to the signing
	// date/time if successful. The 1st signature is at index 0.
	bool GetSignatureSigningTime(int index, CkDateTimeW &dt);

	// Returns the signing certificate for the Nth signature. The 1st signature is at
	// index 0. If successful, the cert is filled with signing certificate.
	bool GetSignerCert(int index, CkCertW &cert);

	// Return the /Name of the Nth signer.
	bool GetSignerName(int index, CkString &outStr);
	// Return the /Name of the Nth signer.
	const wchar_t *getSignerName(int index);
	// Return the /Name of the Nth signer.
	const wchar_t *signerName(int index);

	// Return the signing reason for the Nth signature.
	bool GetSigningReason(int index, CkString &outStr);
	// Return the signing reason for the Nth signature.
	const wchar_t *getSigningReason(int index);
	// Return the signing reason for the Nth signature.
	const wchar_t *signingReason(int index);

	// Returns true if the signature at index includes a signing time.
	bool HasSignatureSigningTime(int index);

	// Open a PDF file and load initial information.
	bool Open(const wchar_t *filePath);

	// Open the PDF file contained in pdfData.
	bool OpenBd(CkBinDataW &pdfData);

	// Verifies all existing signatures contained in the PDF. Returns true if the
	// signatures are valid.
	bool VerifySignatures(void);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
