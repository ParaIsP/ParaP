// CkCsrW.h: interface for the CkCsrW class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat 9.5.0.82

#ifndef _CkCsrW_H
#define _CkCsrW_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkWideCharBase.h"

class CkPrivateKeyW;
class CkBinDataW;
class CkPublicKeyW;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkCsrW
class CK_VISIBLE_PUBLIC CkCsrW  : public CkWideCharBase
{
	

	private:
	
	// Don't allow assignment or copying these objects.
	CkCsrW(const CkCsrW &);
	CkCsrW &operator=(const CkCsrW &);

    public:
	CkCsrW(void);
	virtual ~CkCsrW(void);

	

	static CkCsrW *createNew(void);
	

	
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The common name of the certificate to be generated. For SSL/TLS certificates,
	// this would be the domain name. For email certificates this would be the email
	// address.
	// 
	// It is the value for "CN" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.3")
	// 
	// This property is required for a CSR.
	// 
	void get_CommonName(CkString &str);
	// The common name of the certificate to be generated. For SSL/TLS certificates,
	// this would be the domain name. For email certificates this would be the email
	// address.
	// 
	// It is the value for "CN" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.3")
	// 
	// This property is required for a CSR.
	// 
	const wchar_t *commonName(void);
	// The common name of the certificate to be generated. For SSL/TLS certificates,
	// this would be the domain name. For email certificates this would be the email
	// address.
	// 
	// It is the value for "CN" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.3")
	// 
	// This property is required for a CSR.
	// 
	void put_CommonName(const wchar_t *newVal);

	// The company or organization name for the certificate to be generated.
	// 
	// It is the value for "O" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.10")
	// 
	// This property is optional. It may left empty.
	// 
	void get_Company(CkString &str);
	// The company or organization name for the certificate to be generated.
	// 
	// It is the value for "O" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.10")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *company(void);
	// The company or organization name for the certificate to be generated.
	// 
	// It is the value for "O" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.10")
	// 
	// This property is optional. It may left empty.
	// 
	void put_Company(const wchar_t *newVal);

	// The company division or organizational unit name for the certificate to be
	// generated.
	// 
	// It is the value for "OU" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.11")
	// 
	// This property is optional. It may left empty.
	// 
	void get_CompanyDivision(CkString &str);
	// The company division or organizational unit name for the certificate to be
	// generated.
	// 
	// It is the value for "OU" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.11")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *companyDivision(void);
	// The company division or organizational unit name for the certificate to be
	// generated.
	// 
	// It is the value for "OU" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.11")
	// 
	// This property is optional. It may left empty.
	// 
	void put_CompanyDivision(const wchar_t *newVal);

	// The two-letter uppercase country abbreviation, such as "US", for the certificate
	// to be generated.
	// 
	// It is the value for "C" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.6")
	// 
	// This property is optional. It may left empty.
	// 
	void get_Country(CkString &str);
	// The two-letter uppercase country abbreviation, such as "US", for the certificate
	// to be generated.
	// 
	// It is the value for "C" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.6")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *country(void);
	// The two-letter uppercase country abbreviation, such as "US", for the certificate
	// to be generated.
	// 
	// It is the value for "C" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.6")
	// 
	// This property is optional. It may left empty.
	// 
	void put_Country(const wchar_t *newVal);

	// The email address for the certificate to be generated.
	// 
	// It is the value for "E" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "1.2.840.113549.1.9.1")
	// 
	// This property is optional. It may left empty.
	// 
	void get_EmailAddress(CkString &str);
	// The email address for the certificate to be generated.
	// 
	// It is the value for "E" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "1.2.840.113549.1.9.1")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *emailAddress(void);
	// The email address for the certificate to be generated.
	// 
	// It is the value for "E" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "1.2.840.113549.1.9.1")
	// 
	// This property is optional. It may left empty.
	// 
	void put_EmailAddress(const wchar_t *newVal);

	// The hash algorithm to be used when creating the CSR. The default is SHA256. Can
	// be set to SHA1, SHA384, SHA256, or SHA512.
	void get_HashAlgorithm(CkString &str);
	// The hash algorithm to be used when creating the CSR. The default is SHA256. Can
	// be set to SHA1, SHA384, SHA256, or SHA512.
	const wchar_t *hashAlgorithm(void);
	// The hash algorithm to be used when creating the CSR. The default is SHA256. Can
	// be set to SHA1, SHA384, SHA256, or SHA512.
	void put_HashAlgorithm(const wchar_t *newVal);

	// The locality (city or town) name for the certificate to be generated.
	// 
	// It is the value for "L" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.7")
	// 
	// This property is optional. It may left empty.
	// 
	void get_Locality(CkString &str);
	// The locality (city or town) name for the certificate to be generated.
	// 
	// It is the value for "L" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.7")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *locality(void);
	// The locality (city or town) name for the certificate to be generated.
	// 
	// It is the value for "L" in the certificate's Subject's distinguished name (DN).
	// (This is the value for OID "2.5.4.7")
	// 
	// This property is optional. It may left empty.
	// 
	void put_Locality(const wchar_t *newVal);

	// The state or province for the certificate to be generated.
	// 
	// It is the value for "S" (or "ST") in the certificate's Subject's distinguished
	// name (DN). (This is the value for OID "2.5.4.8")
	// 
	// This property is optional. It may left empty.
	// 
	void get_State(CkString &str);
	// The state or province for the certificate to be generated.
	// 
	// It is the value for "S" (or "ST") in the certificate's Subject's distinguished
	// name (DN). (This is the value for OID "2.5.4.8")
	// 
	// This property is optional. It may left empty.
	// 
	const wchar_t *state(void);
	// The state or province for the certificate to be generated.
	// 
	// It is the value for "S" (or "ST") in the certificate's Subject's distinguished
	// name (DN). (This is the value for OID "2.5.4.8")
	// 
	// This property is optional. It may left empty.
	// 
	void put_State(const wchar_t *newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Generate a CSR and return the binary DER in csrData.
	bool GenCsrBd(CkPrivateKeyW &privKey, CkBinDataW &csrData);

	// Generate a CSR and return it as a PEM string.
	bool GenCsrPem(CkPrivateKeyW &privKey, CkString &outStr);
	// Generate a CSR and return it as a PEM string.
	const wchar_t *genCsrPem(CkPrivateKeyW &privKey);

	// Returns the CSR's public key in the pubkey.
	bool GetPublicKey(CkPublicKeyW &pubkey);

	// Gets a subject field by OID, such as "2.5.4.9". See
	// http://www.alvestrand.no/objectid/2.5.4.html for OID values and meanings.
	bool GetSubjectField(const wchar_t *oid, CkString &outStr);
	// Gets a subject field by OID, such as "2.5.4.9". See
	// http://www.alvestrand.no/objectid/2.5.4.html for OID values and meanings.
	const wchar_t *getSubjectField(const wchar_t *oid);
	// Gets a subject field by OID, such as "2.5.4.9". See
	// http://www.alvestrand.no/objectid/2.5.4.html for OID values and meanings.
	const wchar_t *subjectField(const wchar_t *oid);

	// Loads this CSR object with a CSR PEM. All properties are set to the values found
	// within the CSR.
	bool LoadCsrPem(const wchar_t *csrPemStr);

	// Sets a subject field by OID, such as "2.5.4.9". See
	// http://www.alvestrand.no/objectid/2.5.4.html for OID values and meanings.
	// 
	// The asnType can be "UTF8String", "IA5String", or "PrintableString". If you have no
	// specific requirement, or don't know, choose "UTF8String".
	// 
	bool SetSubjectField(const wchar_t *oid, const wchar_t *value, const wchar_t *asnType);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
