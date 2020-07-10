// CkPdf.h: interface for the CkPdf class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat 9.5.0.76

#ifndef _CkPdf_H
#define _CkPdf_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkMultiByteBase.h"

class CkStringArray;
class CkDateTime;
class CkCert;
class CkBinData;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkPdf
class CK_VISIBLE_PUBLIC CkPdf  : public CkMultiByteBase
{
    private:

	// Don't allow assignment or copying these objects.
	CkPdf(const CkPdf &);
	CkPdf &operator=(const CkPdf &);

    public:
	CkPdf(void);
	virtual ~CkPdf(void);

	static CkPdf *createNew(void);
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
	bool ExtractPageTextSa(int pageNum, CkStringArray &sa);


	// Returns text describing the object contained within the PDF at the pdfPath.
	bool GetObjectInfo(const char *pdfPath, CkString &outStr);

	// Returns text describing the object contained within the PDF at the pdfPath.
	const char *getObjectInfo(const char *pdfPath);
	// Returns text describing the object contained within the PDF at the pdfPath.
	const char *objectInfo(const char *pdfPath);


	// Returns the a page's /Contents.
	bool GetPageContents(int pageNum, CkString &outStr);

	// Returns the a page's /Contents.
	const char *getPageContents(int pageNum);
	// Returns the a page's /Contents.
	const char *pageContents(int pageNum);


	// Gets the signing time for the Nth signature. The dt is set to the signing
	// date/time if successful. The 1st signature is at index 0.
	bool GetSignatureSigningTime(int index, CkDateTime &dt);


	// Returns the signing certificate for the Nth signature. The 1st signature is at
	// index 0. If successful, the cert is filled with signing certificate.
	bool GetSignerCert(int index, CkCert &cert);


	// Return the /Name of the Nth signer.
	bool GetSignerName(int index, CkString &outStr);

	// Return the /Name of the Nth signer.
	const char *getSignerName(int index);
	// Return the /Name of the Nth signer.
	const char *signerName(int index);


	// Return the signing reason for the Nth signature.
	bool GetSigningReason(int index, CkString &outStr);

	// Return the signing reason for the Nth signature.
	const char *getSigningReason(int index);
	// Return the signing reason for the Nth signature.
	const char *signingReason(int index);


	// Returns true if the signature at index includes a signing time.
	bool HasSignatureSigningTime(int index);


	// Open a PDF file and load initial information.
	bool Open(const char *filePath);


	// Open the PDF file contained in pdfData.
	bool OpenBd(CkBinData &pdfData);


	// Verifies all existing signatures contained in the PDF. Returns true if the
	// signatures are valid.
	bool VerifySignatures(void);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
