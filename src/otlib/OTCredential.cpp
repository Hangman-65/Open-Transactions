/*************************************************************
 *
 *  OTCredential.cpp
 *
 */
// A nym contains a list of credentials

// Each credential contains a "master" subkey, and a list of subkeys
// signed by that master.

// The same class (subkey) is used because there are master credentials
// and subkey credentials, so we're using a single "subkey" class to
// encapsulate each credential, both for the master credential and
// for each subkey credential.

// Each subkey has 3 key pairs: encryption, signing, and authentication.

// Each key pair has 2 OTAsymmetricKeys (public and private.)

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA256
 
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, and GUI
 *
 *    	 -- Anonymous Numbered Accounts.
 *    	 -- Untraceable Digital Cash.
 *    	 -- Triple-Signed Receipts.
 *    	 -- Cheques, Vouchers, Transfers, Inboxes.
 *    	 -- Basket Currencies, Markets, Payment Plans.
 *    	 -- Signed, XML, Ricardian-style Contracts.
 *
 *  Copyright (C) 2010-2012 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- OTLib.........A class library.......LICENSE:...LAGPLv3
 *   -- OT-API........A client API..........LICENSE:...LAGPLv3
 *   -- testwallet....Command-line client...LICENSE:...LAGPLv3
 *   -- OT-Server.....Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (livewire_3001@yahoo.com).
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT-API, then you
 *   don't have to open-source your code--only your changes to
 *   Open Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open Transactions terms remain respected, with regard to
 *   the Open Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/OTLib/Lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.11 (Darwin)
 
 iQIcBAEBCAAGBQJOjvvUAAoJEAMIAO35UbuOBlMP/1LX0xJ9CrTOe1G/mgc+VygT
 JPVZDAbQDL/lJXOZMbaPJ/GaLXyEnTViHp97ERrlVuBQz+9uonIKCmPqAGYGVBG1
 MGV2QcscXU2aOUT1VPf2OYEOIul0h8FX2lixfqouH9/OkVsGRLr79Zu8z3zdsO4R
 ktQtjZEU6lnL2t6cmp/cuXlQnbz1xvxd56xNDR11YP07Z4x+CuDB4EAK+P9TfCwn
 tqq5yJmxJM9HtMoi3cUU7kXodKm1n1YZt7O46DOxHqbXqErHChN1ekSK0fXad614
 Gmh+5JfvHjx5XoFWMxb46aAAcUiG8+QpFBcKtSYP2X96k1ylgxMCzrK60ec/MxKV
 BzvP00OJ6PzzrTlcUaCgJ8ZX+0scOMvW0XKioEorozKSWNFvT4Drc4Thhy8u9ET3
 ru1enNFrjdxKjw2+ZTQcKSZjSRx2kMQ2od/dkqUlhe/M1cHGhseH6ls7pItrkykE
 ufZ9GlZoxYE+FRatIBPneT9WwsvFFvH+i6cQ/MM9pbTr19g6VPzVZ4U9E65BbTDB
 czITynH+uMtJLbprtCdQlsI+vqTgYNoY8AUsmnr1qUkp020qGlvwfCJVrooisTmm
 yIh+Yp/KBzySU3inzclaAfv102/t5xi1l+GTyWHiwZxlyt5PBVglKWx/Ust9CIvN
 6h9BYZFTZrh/OwBXCdAv
 =MUfS
 -----END PGP SIGNATURE-----
 **************************************************************/

// in header...
//#include <map>
//#include <string>

// ------------------------------------------------
#include "OTStorage.h"

#include "OTContract.h"
#include "OTAsymmetricKey.h"
#include "OTCredential.h"

#include "OTLog.h"

// ------------------------------------------------



// TODO: Add OTKeypair member for m_pMetadata.
// Add method to set the Metadata. Or instead of a member,
// just have the method set the public and private keys.
//
// Then a Subkey can have a similar function which sets the metadata
// for its three keypairs (they are identical except for the A|E|S.)
//
// When a Nym is loaded, load up its master credentials and all their
// subcredentials. Since their metadata was supposedly set properly at
// creation, verify it at load time.

// TODO: on OTNym, change GetPublicKey to GetPublicKeyForVerify or
// GetPublicKeyForEncrypt or GetPublicKeyForTransmission. Then
// rebuild so that all places using GetPublicKey are forced to choose
// one of those. Same with GetPrivateKeyForSigning, GetPrivateKeyForDecrypt,
// and GetPrivateKeyForAuthentication.


// TODO (start with this) add the methods to OTPseudonym for generating a master
// contract and a sub contract. Add ability to save / load with this data. Then go from there.


OTKeypair::OTKeypair() :
    m_pkeyPublic (OTAsymmetricKey::KeyFactory()),
    m_pkeyPrivate(OTAsymmetricKey::KeyFactory())
{
    
}

OTKeypair::~OTKeypair()
{
    // -----------------------------
    if (NULL != m_pkeyPublic)
        delete m_pkeyPublic; // todo: else error
    if (NULL != m_pkeyPrivate)
        delete m_pkeyPrivate; // todo: else error
    // -----------------------------
	m_pkeyPublic	= NULL;
	m_pkeyPrivate	= NULL;
    // -----------------------------
}
// ---------------------------------------------------------------

bool OTKeypair::HasPublicKey()
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
	return m_pkeyPublic->IsPublic(); // This means it actually has a public key in it, or tried to.
}

bool OTKeypair::HasPrivateKey()
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
	return m_pkeyPrivate->IsPrivate(); // This means it actually has a private key in it, or tried to.
}

// ---------------------------------------------------------------

const OTAsymmetricKey & OTKeypair::GetPublicKey() const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
	return (*m_pkeyPublic);
}
// ---------------------------------------------------------------

const OTAsymmetricKey & OTKeypair::GetPrivateKey() const
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
	return (*m_pkeyPrivate);
}

// ---------------------------------------------------------------

bool OTKeypair::SaveCertToString(OTString & strOutput)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTString strCert;
    
    const bool bSaved = m_pkeyPublic->SaveCertToString(strCert);
    // ---------------------------------------------------------------
	if (bSaved)
        strOutput = strCert;
	
	return bSaved;    
}
// ---------------------------------------------------------------

bool OTKeypair::SavePrivateKeyToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    OTString strPrivateKey;
    
    const bool bSaved = m_pkeyPrivate->SavePrivateKeyToString(strPrivateKey, pstrReason);
    // ---------------------------------------------------------------
	if (bSaved)
        strOutput = strPrivateKey;
	
	return bSaved;
}
// ------------------------------------------------

bool OTKeypair::SaveCertAndPrivateKeyToString(OTString & strOutput, const OTString * pstrReason/*=NULL*/)
{
    OTString strCert, strPrivateKey;
    
    const bool bSaved1 = this->SaveCertToString      (strCert);
    const bool bSaved2 = this->SavePrivateKeyToString(strPrivateKey, pstrReason);
    // ---------------------------------------------------------------
	if (bSaved1 && bSaved2)
		strOutput.Format(const_cast<char*>("%s%s"), strPrivateKey.Get(), strCert.Get());
	
	return (bSaved1 && bSaved2);
}
// ------------------------------------------------

bool OTKeypair::LoadCertAndPrivateKeyFromString(const OTString & strInput, const OTString * pstrReason/*=NULL*/)
{
    const char *szFunc = "OTKeypair::LoadCertAndPrivateKeyFromString";
	// ---------------------------------------------------------------
    OT_ASSERT(strInput.Exists());
	// ---------------------------------------------------------------
    // "escaped" means pre-pended with "- " as in:   - -----BEGIN CER....
    //
    const bool bPublic  = this->LoadPublicKeyFromCertString (strInput, false); //bool bEscaped=true by default
    const bool bPrivate = this->LoadPrivateKeyFromCertString(strInput, false,  //bool bEscaped=true by default,
                                                             pstrReason);
    if (!bPublic)
    {
        OTLog::vError("%s: Although the input string apparently exists, "
                      "LoadPublicKeyFromCertString returned false.\n", szFunc);
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded public key from string.\n",
                       szFunc);
    }
    // ----------------
    if (!bPrivate)
    {
        OTLog::vError("%s: Although the input string apparently exists, "
                      "LoadPrivateKeyFromCertString returned false.\n", szFunc);
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded private key from string.\n", szFunc);
    }
    // ----------------
    return true;
}

// ------------------------------------------------

bool OTKeypair::SaveAndReloadBothKeysFromTempFile(      OTString * pstrOutputCert/*=NULL*/,
                                                  const OTString * pstrReason/*=NULL*/)
{
    const char * szFunc = " OTKeypair::SaveAndReloadBothKeysFromTempFile";
	// ---------------------------------------------------------------
    OT_ASSERT(NULL != m_pkeyPrivate);
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTString    strOutput;
    const bool  bSuccess   = this->SaveCertAndPrivateKeyToString(strOutput, pstrReason);
	// ---------------------------------------
	if (bSuccess)
	{
        // todo security. Revisit this part during security audit.
        //
		const OTString strFilename("temp.nym"); // todo stop hardcoding. Plus this maybe should select a random number too.
        
		if (false == OTDB::StorePlainString(strOutput.Get(), OTFolders::Cert().Get(), strFilename.Get())) // temp.nym
		{
			OTLog::vError("%s: Failure storing new cert in temp file: %s\n", szFunc, strFilename.Get());
			return false;
		}
		// ------------------------------------------
        if (false == this->LoadBothKeysFromCertFile(OTFolders::Cert().Get(), strFilename, pstrReason))
            return false; // LoadBothKeysFromCertFile already has error logs, no need to log twice at this point.
		// ------------------------------------------
        if (NULL != pstrOutputCert)
            pstrOutputCert->Set(strOutput); // Success!
	}
	
	return bSuccess;   
}


// ---------------------------------------------------------------
// Load from local storage.
bool OTKeypair::LoadPrivateKey(const OTString & strFoldername,
                               const OTString & strFilename, const OTString * pstrReason/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->LoadPrivateKey(strFoldername, strFilename, pstrReason);
}

bool OTKeypair::LoadPublicKey (const OTString & strFoldername,
                               const OTString & strFilename)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKey(strFoldername, strFilename);
}

// ***************************************************************
// LoadPrivateKeyFromCertString
//
// "escaped" means pre-pended with "- " as in:   - -----BEGIN CERTIFICATE....
//
bool OTKeypair::LoadPrivateKeyFromCertString(const OTString & strCert, bool bEscaped/*=true*/, const OTString * pstrReason/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->LoadPrivateKeyFromCertString(strCert, bEscaped, pstrReason);
}

// ***************************************************************
// Load Public Key from Cert (file or string)
//
bool OTKeypair::LoadPublicKeyFromCertString(const OTString & strCert, bool bEscaped/*=true*/) // DOES handle bookends, AND escapes.
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKeyFromCertString(strCert, bEscaped);
}

bool OTKeypair::LoadPublicKeyFromCertFile(const OTString & strFoldername, const OTString & strFilename) // DOES handle bookends.
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->LoadPublicKeyFromCertFile(strFoldername, strFilename);
}



bool OTKeypair::MakeNewKeypair(int nBits/*=1024*/)
{
    const char * szFunc = "OTKeypair::MakeNewKeypair";
	// ---------------------------------------------------------------
    OT_ASSERT(NULL != m_pkeyPrivate);
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    OTLowLevelKeyData lowLevelData;
    
    if (!lowLevelData.MakeNewKeypair(nBits))
    {
        OTLog::vError("%s: Failed in a call to OTLowLevelKeyData::MakeNewKeypair(%d).\n",
                      szFunc, nBits);
        return false;
    }
    // ---------------------------------------------------------------
    return lowLevelData.SetOntoKeypair(*this);
    
    // If true is returned:
    // Success! At this point, theKeypair's public and private keys have been set.
    // Keep in mind though, they still won't be "quite right" until saved and loaded
    // again, at least according to existing logic. That saving/reloading is currently
    // performed in OTPseudonym::GenerateNym().
}



bool OTKeypair::LoadBothKeysFromCertFile(const OTString & strFoldername,
                                         const OTString & strFilename,
                                         const OTString * pstrReason/*=NULL*/)
{
    const char * szFunc = "OTKeypair::LoadBothKeysFromCertFile";
    // -------------------------------------
    OT_ASSERT(NULL != m_pkeyPublic);
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    bool bPublic  = false;
    bool bPrivate = false;
    
    bPublic  = m_pkeyPublic-> LoadPublicKeyFromCertFile (strFoldername.Get(), strFilename.Get());
    bPrivate = m_pkeyPrivate->LoadPrivateKey            (strFoldername.Get(), strFilename.Get(),
                                                         pstrReason);
    if (!bPublic)
    {
        OTLog::vError("%s: Although the ascii-armored file (%s) was read, LoadPublicKeyFromCert "
                      "returned false.\n", szFunc, strFilename.Get());
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded public key from Certfile: %s\n",
                       szFunc, strFilename.Get());
    }
    // -----------------
    if (!bPrivate)
    {
        OTLog::vError("%s: Although the ascii-armored file (%s) was read, LoadPrivateKey returned false.\n",
                      szFunc, strFilename.Get());
        return false;
    }
    else
    {
        OTLog::vOutput(2, "%s: Successfully loaded private key from certfile: %s\n",
                       szFunc, strFilename.Get());
    }
    // -----------------------------------------
    return true;
}


bool OTKeypair::SignContract(OTContract & theContract, OTPasswordData  * pPWData/*=NULL*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // --------------------------------------------
    return theContract.SignWithKey(*m_pkeyPrivate, pPWData);
}



// ***************************************************************************************
// PUBLIC KEY

// * Get the public key in ASCII-armored format                 -- OTASCIIArmor
// * Get the public key in ASCII-armored format WITH bookends   -- OTString
//       - ------- BEGIN PUBLIC KEY --------
//       Notice the "- " before the rest of the bookend starts.
//
bool OTKeypair::GetPublicKey(OTASCIIArmor & strKey) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->GetPublicKey(strKey);
}

bool OTKeypair::GetPublicKey(OTString & strKey, bool bEscaped/*=true*/) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->GetPublicKey(strKey, bEscaped);
}

// -----------------------------------------------------------------------
// (Below) Decodes a public key from ASCII armor into an actual key pointer
// and sets that as the m_pKey on this object.
//
bool OTKeypair::SetPublicKey(const OTASCIIArmor & strKey)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->SetPublicKey(strKey);
}


// Decodes a public key from bookended key string into an actual key
// pointer, and sets that as the m_pPublicKey on this object.
// This is the version that will handle the bookends ( -----BEGIN PUBLIC KEY-----)
//
bool OTKeypair::SetPublicKey(const OTString & strKey, bool bEscaped/*=false*/)
{
    OT_ASSERT(NULL != m_pkeyPublic);
    
    // ---------------------------------------------------------------
    if (strKey.Contains("PGP PUBLIC KEY"))
	{
		OTASCIIArmor theArmor;
		
		if (theArmor.LoadFromString(const_cast<OTString &>(strKey), bEscaped))
		{
			// This function expects that the bookends are already removed.
			// The ascii-armor loading code removes them and handles the escapes also.
			return m_pkeyPublic->LoadPublicKeyFromPGPKey(theArmor);
		}
		else
        {
			OTLog::Output(2, "OTKeypair::SetPublicKey: Failed extracting PGP public key from ascii-armored text.\n");
			return false;
		}
	}
	else // the below function SetPublicKey (in the return call) expects the
        // bookends to still be there, and it will handle removing them. (Unlike PGP code above.)
		return m_pkeyPublic->SetPublicKey(strKey, bEscaped);

    return false;
}

// ***************************************************************************************
// PRIVATE KEY
// Get the private key in ASCII-armored format with bookends
// - ------- BEGIN ENCRYPTED PRIVATE KEY --------
// Notice the "- " before the rest of the bookend starts.
//
bool OTKeypair::GetPrivateKey(OTString & strKey, bool bEscaped/*=true*/) const
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->GetPrivateKey(strKey, bEscaped);
}

bool OTKeypair::GetPrivateKey(OTASCIIArmor & strKey) const  // Get the private key in ASCII-armored format
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->GetPrivateKey(strKey);
}

// Decodes a private key from ASCII armor into an actual key pointer
// and sets that as the m_pPrivateKey on this object.
// This is the version that will handle the bookends ( -----BEGIN ENCRYPTED PRIVATE KEY-----)
bool OTKeypair::SetPrivateKey(const OTString & strKey, bool bEscaped/*=false*/)
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    const char * szOverride = "PGP PRIVATE KEY";

	if (strKey.Contains(szOverride))
	{
		OTASCIIArmor theArmor;
        
		if (theArmor.LoadFromString(const_cast<OTString &>(strKey), bEscaped,
                                    szOverride)) // szOverride == "PGP PRIVATE KEY"
		{
			// This function expects that the bookends are already removed.
			// The ascii-armor loading code removes them and handles the escapes also.
//			return m_pkeyPrivate->LoadPrivateKeyFromPGPKey(theArmor);
            //
			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 1: Failure: PGP private keys are NOT YET SUPPORTED:\n\n%s\n\n",
                           strKey.Get());
			return false;
		}
		else 
        {
			OTLog::vOutput(0, "OTKeypair::SetPrivateKey 2: Failure: PGP private keys are NOT YET SUPPORTED:\n\n%s\n\n",
                           strKey.Get());
			return false;
		}
	}
	else // the below function SetPrivateKey (in the return call) expects the
         // bookends to still be there, and it will handle removing them. (Unlike PGP code above.)
        //
		return m_pkeyPrivate->SetPrivateKey(strKey, bEscaped);
}

bool OTKeypair::SetPrivateKey(const OTASCIIArmor & strKey) // Decodes a private key from ASCII armor into an actual key pointer and sets that as the m_pKey on this object.
{
    OT_ASSERT(NULL != m_pkeyPrivate);
    // ---------------------------------------------------------------
    return m_pkeyPrivate->SetPrivateKey(strKey);
}

bool OTKeypair::CalculateID(OTIdentifier & theOutput) const
{
    OT_ASSERT(NULL != m_pkeyPublic);
    // ---------------------------------------------------------------
    return m_pkeyPublic->CalculateID(theOutput); // Only works for public keys.
}

// ***************************************************************************************







// Contains 3 key pairs: signing, authentication, and encryption.
// This is stored as an OTContract, and it must be signed by the
// master key. (which is also an OTSubcredential.)
//

void OTSubcredential::SetOwner(OTCredential & theOwner)
{
    m_pOwner = &theOwner;
}
// ----------------------------------------------------------------
OTSubcredential::OTSubcredential()
: ot_super(), m_StoreAs(OTSubcredential::credPrivateInfo), m_pOwner(NULL)       { }
// ----------------------------------------------------------------
OTSubcredential::OTSubcredential(OTCredential & theOwner)
: ot_super(), m_StoreAs(OTSubcredential::credPrivateInfo), m_pOwner(&theOwner)  { }
// ----------------------------------------------------------------
OTSubcredential::~OTSubcredential()
{
    Release_Subcredential();
    
}

// ----------------------------------------------------------------

//virtual
void OTSubcredential::Release()
{
    Release_Subcredential();  // My own cleanup is done here.
    
    // Next give the base class a chance to do the same...
	ot_super::Release(); // since I've overridden the base class, I call it now...
}

// ----------------------------------------------------------------

    
void OTSubcredential::Release_Subcredential()
{
    // Release any dynamically allocated members here. (Normally.) 
}

// ----------------------------------------------------------------

//virtual
bool OTSubcredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    m_mapPublicInfo   = mapPublic;
    return true;
}


//virtual
bool OTSubcredential::SetPrivateContents(const mapOfStrings & mapPrivate)
{
    m_mapPrivateInfo  = mapPrivate;
    return true;
}

void OTSubcredential::SetMasterCredID(const OTString & strMasterCredID)
{
    m_strMasterCredID = strMasterCredID;
}

void OTSubcredential::SetNymIDandSource(const OTString & strNymID, const OTString & strSourceForNymID)
{
    m_strNymID          = strNymID;
    m_strSourceForNymID = strSourceForNymID;
}


// -------------------------------------------------------------------

void OTSubcredential::UpdateMasterPublicToString(OTString & strAppendTo) // Used in UpdateContents.
{
    OT_ASSERT(NULL != m_pOwner);
    OTASCIIArmor ascMaster(m_pOwner->GetContents());
    strAppendTo.Concatenate("<masterPublic>\n%s</masterPublic>\n\n",
                            ascMaster.Get());
}

void OTSubcredential::UpdatePublicContentsToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (m_mapPublicInfo.size() > 0)
    {
        strAppendTo.Concatenate("<publicContents count=\"%d\">\n\n", m_mapPublicInfo.size());
        
        FOR_EACH(mapOfStrings, m_mapPublicInfo)
        {
            OTString     strInfo((*it).second);
            OTASCIIArmor ascInfo(strInfo);
            strAppendTo.Concatenate("<publicInfo key=\"%s\">\n%s</publicInfo>\n\n",
                                      (*it).first.c_str(), ascInfo.Get());
        }
        // ------------------------------
        strAppendTo.Concatenate("</publicContents>\n\n");
    }
}

void OTSubcredential::UpdatePublicCredentialToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (this->GetContents().Exists())
    {
        OTASCIIArmor ascContents(this->GetContents());
        if (ascContents.Exists())
            strAppendTo.Concatenate("<publicCredential>\n%s</publicCredential>\n\n",
                                    ascContents.Get());
    }    
}

void OTSubcredential::UpdatePrivateContentsToString(OTString & strAppendTo) // Used in UpdateContents.
{
    if (m_mapPrivateInfo.size() > 0)
    {
        strAppendTo.Concatenate("<privateContents count=\"%d\">\n\n", m_mapPrivateInfo.size());
        
        FOR_EACH(mapOfStrings, m_mapPrivateInfo)
        {
            OTString     strInfo((*it).second);
            OTASCIIArmor ascInfo(strInfo);
            strAppendTo.Concatenate("<privateInfo key=\"%s\">\n%s</privateInfo>\n\n",
                                    (*it).first.c_str(), ascInfo.Get());
        }
        strAppendTo.Concatenate("</privateContents>\n\n");
    }
}

void OTSubcredential::UpdateContents()
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<subCredential nymID=\"%s\"\n" // a hash of the nymIDSource
							  " nymIDSource=\"%s\"\n" // A nym should always verify through its own source. (Whatever that may be.)
							  " masterCredentialID=\"%s\" >\n\n", // Hash of the master credential that signed this subcredential.
							  this->GetNymID().Get(), this->GetNymIDSource().Get(),
                              this->GetMasterCredID().Get());
    // --------------------------------------------
//  if (OTSubcredential::credPublicInfo == m_StoreAs)  // (Always saving public info.)
    {
        // *****************************************************
        // PUBLIC INFO
        this->UpdateMasterPublicToString(m_xmlUnsigned);
        // --------------------------------------------
        this->UpdatePublicContentsToString(m_xmlUnsigned);
        // *****************************************************
    }
	// -------------------------------------------------
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</subCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}


// ------------------------------


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int OTSubcredential::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	int nReturnVal = 0;
	
    const OTString strNodeName(xml->getNodeName());

	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do in the case of OTAccount.
    //
	// if (nReturnVal = OTContract::ProcessXMLNode(xml))
    //	  return nReturnVal;
	
    // --------------------------------------------------
	if (strNodeName.Compare("subCredential"))
	{
		m_strNymID			= xml->getAttributeValue("nymID");
		m_strSourceForNymID	= xml->getAttributeValue("nymIDSource");
		m_strMasterCredID	= xml->getAttributeValue("masterCredentialID");
		
		OTLog::Output(1, "Loading subcredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("masterPublic"))
	{
        OTString strMasterPublicCredential;
        
		if (false == OTContract::LoadEncodedTextField(xml, strMasterPublicCredential))
		{
			OTLog::vError("Error in %s line %d: failed loading expected master public credential while loading subcredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
        // Verify the master public credential we loaded against the one we expected to get, according
        // to the OTCredential that is m_pOwner.
        //
        else if ((NULL != m_pOwner) && false == (m_pOwner->GetContents().Compare(strMasterPublicCredential)))
        {
            OTLog::vError("Failure in %s line %d: while loading subcredential: master public "
                          "credential loaded just now, doesn't match the actual master public credential, "
                          "according to the current owner object.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
        }
		
		nReturnVal = 1;
	}
	// ------------------------------------------------------------------------------------
	else if (strNodeName.Compare("publicContents"))
	{
        OTString strCount;
        strCount = xml->getAttributeValue("count");
        const int nCount = strCount.Exists() ? atoi(strCount.Get()) : 0;
        if (nCount > 0)
        {
            int nTempCount = nCount;
            mapOfStrings mapPublic;
            
            while (nTempCount-- > 0)
            {
                // -----------------------------------------------                
                const char	*	pElementExpected	= "publicInfo";
                OTString		strPublicInfo;
                
                // This map contains values we will also want, when we read the info...
                // (The OTContract::LoadEncodedTextField call below will read all the values
                // as specified in this map.)
                //
                mapOfStrings	temp_MapAttributes;
                temp_MapAttributes.insert(std::pair<std::string, std::string>("key", "")); // Value should be "A" or "E" or "S" after reading.
                
                if (false == OTContract::LoadEncodedTextFieldByName(xml, strPublicInfo, pElementExpected, &temp_MapAttributes)) // </publicInfo>
                {
                    OTLog::vError("%s: Error: "
                                  "Expected %s element with text field.\n", __FUNCTION__,
                                  pElementExpected);
                    return (-1); // error condition
                }
                // ------------------------------------------
                mapOfStrings::iterator it = temp_MapAttributes.find("key");                
                if ((it != temp_MapAttributes.end())) // We expected this much.
                {
                    std::string & str_key = (*it).second;
                    
                    if (str_key.size() > 0) // Success finding key type ('A' 'E' or 'S')
                    {
                        // ---------------------------------------
                        mapPublic.insert(std::pair<std::string, std::string>(str_key, strPublicInfo.Get()));
                        // ---------------------------------------
                    }
                    // else it's empty, which is expected if nothing was there, since that's the default value
                    // that we set above for "name" in temp_MapAttributes.
                    else
                    {
                        OTLog::vError("%s: Expected key type of 'A' or 'E' or 'S'.\n", __FUNCTION__);
                        return (-1); // error condition
                    }
                }
                else
                {
                    OTLog::vError("%s: Strange error: couldn't find key type AT ALL.\n", __FUNCTION__); // should never happen.
                    return (-1); // error condition
                }
            } // while
            // --------------------------------
            if (mapPublic.size() != nCount)
            {
                OTLog::vError("%s, %s, %d: Subcredential expected to load %d publicInfo objects, "
                              "but actually loaded %d. (Mismatch, failure loading.)\n",
                              __FUNCTION__, __FILE__, __LINE__, nCount, mapPublic.size());
                return (-1); // error condition
            }
            // --------------------------------
            if (false == this->SetPublicContents(mapPublic))  // <==============  Success.
            {
                OTLog::vError("%s, %s, %d: Subcredential failed setting public contents while loading.\n",
                              __FUNCTION__, __FILE__, __LINE__);
                return (-1); // error condition    
            }
            // --------------------------------            
        } // if strCount.Exists() && nCount > 0
        // -------------------------------------------------------------------------------
		OTLog::Output(2, "Loaded publicContents for subcredential.\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("publicCredential"))
	{
		if (false == OTContract::LoadEncodedTextField(xml, m_strContents)) // <========= m_strContents.
		{
			OTLog::vError("Error in %s line %d: failed loading expected public credential while loading private subcredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("privateContents"))
	{
        OTString strCount;
        strCount = xml->getAttributeValue("count");
        const int nCount = strCount.Exists() ? atoi(strCount.Get()) : 0;
        if (nCount > 0)
        {
            int nTempCount = nCount;
            mapOfStrings mapPrivate;
            
            while (nTempCount-- > 0)
            {
                // -----------------------------------------------                
                const char	*	pElementExpected	= "privateInfo";
                OTString		strPrivateInfo;
                
                // This map contains values we will also want, when we read the info...
                // (The OTContract::LoadEncodedTextField call below will read all the values
                // as specified in this map.)
                //
                mapOfStrings	temp_MapAttributes;
                temp_MapAttributes.insert(std::pair<std::string, std::string>("key", "")); // Value should be "A" or "E" or "S" after reading.
                
                if (false == OTContract::LoadEncodedTextFieldByName(xml, strPrivateInfo, pElementExpected, &temp_MapAttributes)) // </privateInfo>
                {
                    OTLog::vError("%s: Error: "
                                  "Expected %s element with text field.\n", __FUNCTION__,
                                  pElementExpected);
                    return (-1); // error condition
                }
                // ------------------------------------------
                mapOfStrings::iterator it = temp_MapAttributes.find("key");                
                if ((it != temp_MapAttributes.end())) // We expected this much.
                {
                    std::string & str_key = (*it).second;
                    
                    if (str_key.size() > 0) // Success finding key type ('A' 'E' or 'S')
                    {
                        // ---------------------------------------
                        mapPrivate.insert(std::pair<std::string, std::string>(str_key, strPrivateInfo.Get()));
                        // ---------------------------------------
                    }
                    // else it's empty, which is expected if nothing was there, since that's the default value
                    // that we set above for "name" in temp_MapAttributes.
                    else
                    {
                        OTLog::vError("%s: Expected key type of 'A' or 'E' or 'S'.\n", __FUNCTION__);
                        return (-1); // error condition
                    }
                }
                else
                {
                    OTLog::vError("%s: Strange error: couldn't find key type AT ALL.\n", __FUNCTION__); // should never happen.
                    return (-1); // error condition
                }
            } // while
            // --------------------------------
            if (mapPrivate.size() != nCount)
            {
                OTLog::vError("%s, %s, %d: Subcredential expected to load %d privateInfo objects, "
                              "but actually loaded %d. (Mismatch, failure loading.)\n",
                              __FUNCTION__, __FILE__, __LINE__, nCount, mapPrivate.size());
                return (-1); // error condition
            }
            // --------------------------------
            if (false == this->SetPrivateContents(mapPrivate))
            {
                OTLog::vError("%s, %s, %d: Subcredential failed setting private contents while loading.\n",
                              __FUNCTION__, __FILE__, __LINE__);
                return (-1); // error condition    
            }
            // --------------------------------            
        } // if strCount.Exists() && nCount > 0
        // -------------------------------------------------------------------------------
		OTLog::Output(2, "Loaded privateContents for subcredential.\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	return nReturnVal;
}


// -------------------------------------------------------------------


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int OTSubkey::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	int nReturnVal = ot_super::ProcessXMLNode(xml);
	
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do in the case of OTAccount.
    //
	if (0 != nReturnVal)
       return nReturnVal;
	// else it was 0 (continue...)
    // --------------------------------------------------
    const OTString strNodeName(xml->getNodeName());
    // --------------------------------------------------
	if (strNodeName.Compare("keyCredential"))
	{
		m_strNymID			= xml->getAttributeValue("nymID");
		m_strSourceForNymID	= xml->getAttributeValue("nymIDSource");
		m_strMasterCredID	= xml->getAttributeValue("masterCredentialID");
		
		OTLog::Output(1, "Loading keyCredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	else if (strNodeName.Compare("masterSigned"))
	{
		if (false == OTContract::LoadEncodedTextField(xml, m_strMasterSigned))
		{
			OTLog::vError("Error in %s line %d: failed loading expected master-signed version while loading keyCredential.\n",
                          __FILE__, __LINE__);
			return (-1); // error condition
		}
		
		nReturnVal = 1;
	}
	// ------------------
	return nReturnVal;
}


// -------------------------------------------------------------------

void OTSubkey::UpdateContents()
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<keyCredential nymID=\"%s\"\n" // a hash of the nymIDSource
							  " nymIDSource=\"%s\"\n" // A nym should always verify through its own source. (Whatever that may be.) Perhaps a Namecoin address containing a list of master credential IDs.
							  " masterCredentialID=\"%s\" >\n\n", // Hash of the master credential that signed this subcredential.
							  this->GetNymID().Get(), this->GetNymIDSource().Get(),
                              this->GetMasterCredID().Get());
    // --------------------------------------------
    // MASTER-SIGNED INFO
    //
    if ((OTSubcredential::credMasterSigned == m_StoreAs) || // MASTER-SIGNED INFO
        (OTSubcredential::credPrivateInfo  == m_StoreAs))
    {
        // --------------------------------------------
        this->UpdateMasterPublicToString(m_xmlUnsigned);
        // --------------------------------------------
        this->UpdatePublicContentsToString(m_xmlUnsigned);
    }
    // --------------------------------------------
    // PUBLIC INFO
    //
    if ((OTSubcredential::credPublicInfo  == m_StoreAs)  || // PUBLIC INFO (signed by subkey, contains master signed info.)
        (OTSubcredential::credPrivateInfo == m_StoreAs))
    {
        OTASCIIArmor ascMasterSigned(this->GetMasterSigned()); // GetMasterSigned() returns the contract containing the master-signed contents from the above block.
        m_xmlUnsigned.Concatenate("<masterSigned>\n%s</masterSigned>\n\n", // Contains all the public info, signed by the master key.
                                  ascMasterSigned.Get());                  // Packaged up here inside a final, subkey-signed credential.
    }
	// -------------------------------------------------
    // PRIVATE INFO
    //
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)  // PRIVATE INFO
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</keyCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}

// -------------------------------------------------------------------


// return -1 if error, 0 if nothing, and 1 if the node was processed.
//
int OTMasterkey::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	int nReturnVal = ot_super::ProcessXMLNode(xml);
	
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do in the case of OTAccount.
    //
	if (0 != nReturnVal)
       return nReturnVal;
	// else it was 0 (continue...)
    // --------------------------------------------------
    const OTString strNodeName(xml->getNodeName());
    // --------------------------------------------------
	if (strNodeName.Compare("masterCredential"))
	{
		m_strNymID			= xml->getAttributeValue("nymID");
		m_strSourceForNymID	= xml->getAttributeValue("nymIDSource");

		m_strMasterCredID.Release();
		
		OTLog::Output(1, "Loading masterCredential...\n");
		
		nReturnVal = 1;
	}
	// ----------------------------------
	return nReturnVal;
}


// -------------------------------------------------------------------

void OTMasterkey::UpdateContents() 
{
	m_xmlUnsigned.Release();
    
	m_xmlUnsigned.Concatenate("<masterCredential nymID=\"%s\"\n" // a hash of the nymIDSource
							  " nymIDSource=\"%s\" >\n\n", // A nym should always verify through its own source. (Whatever that may be.)
							  this->GetNymID().Get(), this->GetNymIDSource().Get());
    // --------------------------------------------
    // PUBLIC INFO
    //
//  if (OTSubcredential::credPublicInfo == m_StoreAs)   // PUBLIC INFO  (Always save this in every state.)
    {        
        this->UpdatePublicContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------
    // PRIVATE INFO
    //
    // If we're saving the private credential info...
    // 
    if (OTSubcredential::credPrivateInfo == m_StoreAs)   // PRIVATE INFO
    {
        this->UpdatePublicCredentialToString(m_xmlUnsigned);
        // -------------------------------------
        this->UpdatePrivateContentsToString(m_xmlUnsigned);
    }
	// -------------------------------------------------	
	m_xmlUnsigned.Concatenate("</masterCredential>\n");
    // --------------------------------------------
    m_StoreAs = OTSubcredential::credPrivateInfo;  // <=== SET IT BACK TO DEFAULT BEHAVIOR. Any other state processes ONCE, and then goes back to this again.
}



// ***************************************************************************************

//         OTLog::vError("%s line %d: \n", __FILE__, __LINE__);


OTKeyCredential::OTKeyCredential()                        : ot_super()         { }
OTKeyCredential::OTKeyCredential(OTCredential & theOwner) : ot_super(theOwner) { }

OTKeyCredential::~OTKeyCredential()
{
    Release_Subkey();
}

//virtual
void OTKeyCredential::Release()
{
    Release_Subkey();   // My own cleanup is done here.
    
    // Next give the base class a chance to do the same...
	ot_super::Release(); // since I've overridden the base class, I call it now...
}
    
void OTKeyCredential::Release_Subkey()
{
    // Release any dynamically allocated members here. (Normally.)
}
// --------------------------------------

bool OTKeyCredential::GenerateKeys(int nBits/*=1024*/)       // Gotta start somewhere.
{
    const bool bSign = m_SigningKey.MakeNewKeypair(nBits);
    
    if (bSign)
    {
        const bool bAuth = m_AuthentKey.MakeNewKeypair(nBits);
        
        if (bAuth)
        {
            const bool bEncr = m_EncryptKey.MakeNewKeypair(nBits);
            // ------------------------------------------------
            if (bEncr)
            {
                // Since the keys were all generated successfully, we need to copy their
                // certificate data into the m_mapPublicInfo and m_mapPrivateInfo (string maps.)
                //
                OTString     strPublicKey, strPrivateCert;
                mapOfStrings mapPublic,    mapPrivate;
                // ------------------------------------------
                const OTString strReason("Generating keys for new credential...");
                // ------------------------------------------                
                const bool b1 = m_SigningKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
                const bool b2 = m_SigningKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);
                
                if (b1)
                    mapPublic. insert(std::pair<std::string, std::string>("S", strPublicKey.Get()));
                if (b2)
                    mapPrivate.insert(std::pair<std::string, std::string>("S", strPrivateCert.Get()));
                // ------------------------------------------------------------------------------------------
                strPublicKey.  Release();
                strPrivateCert.Release();
                const bool b3 = m_AuthentKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
                const bool b4 = m_AuthentKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);                
                
                if (b3)
                    mapPublic. insert(std::pair<std::string, std::string>("A", strPublicKey.Get()));
                if (b4)
                    mapPrivate.insert(std::pair<std::string, std::string>("A", strPrivateCert.Get()));
                // ------------------------------------------------------------------------------------------
                strPublicKey.  Release();
                strPrivateCert.Release();
                const bool b5 = m_EncryptKey.GetPublicKey(strPublicKey, false); // bEscaped=true by default.
                const bool b6 = m_EncryptKey.SaveCertAndPrivateKeyToString(strPrivateCert, &strReason);
                
                if (b5)
                    mapPublic. insert(std::pair<std::string, std::string>("E", strPublicKey.Get()));
                if (b6)
                    mapPrivate.insert(std::pair<std::string, std::string>("E", strPrivateCert.Get()));
                // ------------------------------------------
                if (3 != mapPublic.size())
                {
                    OTLog::vError("In %s, line %d: Failed getting public keys in OTKeyCredential::GenerateKeys.\n",
                                  __FILE__, __LINE__);
                    return false;
                }
                else
                    this->ot_super::SetPublicContents(mapPublic);
                // --------------------------------
                if (3 != mapPrivate.size())
                {
                    OTLog::vError("In %s, line %d: Failed getting private keys in OTKeyCredential::GenerateKeys.\n",
                                  __FILE__, __LINE__);
                    return false;
                }
                else
                    this->ot_super::SetPrivateContents(mapPrivate);
                // --------------------------------
                return true;
            }
        }
    }
    return false;
}
// --------------------------------------

//virtual
bool OTKeyCredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    // NOTE: We might use this on the server side, we'll see, but so far on the client
    // side, we won't need to use this function, since SetPrivateContents already does
    // the dirty work of extracting the public keys and setting them.
    //
    // -------------------------------------------------
    if (mapPublic.size() != 3)
    {
        OTLog::vError("%s line %d: Failure: Expected 3 in mapPublic.size(), but the actual value was: %d\n",
                      __FILE__, __LINE__, mapPublic.size());
        return false;
    }
    // -------------------------------------------------
    mapOfStrings::const_iterator iiAuth = mapPublic.find("A");  // Authentication key
    mapOfStrings::const_iterator iiEncr = mapPublic.find("E");  // Encryption key
    mapOfStrings::const_iterator iiSign = mapPublic.find("S");  // Signing key
    // -------------------------------------------------
    if (mapPublic.end() == iiAuth)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public authentication key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPublic.end() == iiEncr)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public encryption key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPublic.end() == iiSign)
    {
        OTLog::vError("%s line %d: Failure: Unable to find public signing key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (this->ot_super::SetPublicContents(mapPublic))
    {
        // -------------------------------------------------
        OTString strKey;
        strKey.Set((*iiAuth).second.c_str());
        if (false == m_AuthentKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public authentication key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        strKey.Release();
        strKey.Set((*iiEncr).second.c_str());
        if (false == m_EncryptKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public encryption key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        strKey.Release();
        strKey.Set((*iiSign).second.c_str());
        if (false == m_SigningKey.SetPublicKey(strKey))
        {
            OTLog::vError("%s line %d: Failure: Unable to set public signing key based on string:\n%s\n",
                          __FILE__, __LINE__, strKey.Get());
            return false;
        }
        // -------------------------------------------------
        return true; // SUCCESS! This means the input, mapPublic, actually contained an "A" key, an "E"
        // key, and an "S" key (and nothing else) and that all three of those public keys actually loaded
        // from string form into their respective key object members.
    }
    // -------------------------------------------------
    return false;
}



// -------------------------------------------------
// NOTE: With OTKeyCredential, if you call SetPrivateContents, you don't have to call SetPublicContents,
// since SetPrivateContents will automatically set the public contents, since the public certs are available
// from the private certs. Not all credentials do this, but keys do. So you might ask, why did I still
// provide a version of SetPublicContents for OTKeyCredential? Just to fit the convention, also also because
// perhaps on the server side, public contents will be the only ones available, and private ones will never
// be set.

//virtual
bool OTKeyCredential::SetPrivateContents(const mapOfStrings & mapPrivate)
{
    // -------------------------------------------------
    if (mapPrivate.size() != 3)
    {
        OTLog::vError("%s line %d: Failure: Expected 3 in mapPrivate(), but the actual value was: %d\n",
                      __FILE__, __LINE__, mapPrivate.size());
        return false;
    }
    // -------------------------------------------------
    mapOfStrings::const_iterator iiAuth = mapPrivate.find("A");  // Authentication key
    mapOfStrings::const_iterator iiEncr = mapPrivate.find("E");  // Encryption key
    mapOfStrings::const_iterator iiSign = mapPrivate.find("S");  // Signing key
    // -------------------------------------------------
    if (mapPrivate.end() == iiAuth)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private authentication key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPrivate.end() == iiEncr)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private encryption key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (mapPrivate.end() == iiSign)
    {
        OTLog::vError("%s line %d: Failure: Unable to find private signing key.\n", __FILE__, __LINE__);
        return false;
    }
    // -------------------------------------------------
    if (this->ot_super::SetPrivateContents(mapPrivate))
    {
        const OTString strReason("Loading private key from credential.");
        mapOfStrings mapPublic;
        // -------------------------------------------------
        OTString strPrivate;
        strPrivate.Set((*iiAuth).second.c_str()); // strPrivate now contains the private Cert string.
        
        if (false == m_AuthentKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped is true by default*/,  &strReason))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private authentication key based on string:\n%s\n",
                          __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;

            if ((false == m_AuthentKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped is true by default */)) ||
                (false == m_AuthentKey.GetPublicKey(strPublic, false /* bEscaped is true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public authentication key based on private string:\n%s\n",
                              __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("A", strPublic.Get()));
        }
        // -------------------------------------------------
        strPrivate.Release();
        strPrivate.Set((*iiEncr).second.c_str());
        
        if (false == m_EncryptKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped is true by default*/,  &strReason))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private encryption key based on string:\n%s\n",
                          __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;
            
            if ((false == m_EncryptKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped is true by default */)) ||
                (false == m_EncryptKey.GetPublicKey(strPublic, false /* bEscaped is true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public encryption key based on private string:\n%s\n",
                              __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("E", strPublic.Get()));
        }
        // -------------------------------------------------
        strPrivate.Release();
        strPrivate.Set((*iiSign).second.c_str());
        
        if (false == m_SigningKey.LoadPrivateKeyFromCertString(strPrivate, false /*bEscaped is true by default*/,  &strReason))
        {
            OTLog::vError("%s line %d: Failure: Unable to set private signing key based on string:\n%s\n",
                          __FILE__, __LINE__, strPrivate.Get());
            return false;
        }
        else // Success loading the private key. Let's grab the public key here.
        {
            OTString strPublic;
            
            if ((false == m_SigningKey.LoadPublicKeyFromCertString(strPrivate, false /* bEscaped is true by default */)) ||
                (false == m_SigningKey.GetPublicKey(strPublic, false /* bEscaped is true by default */)))
            {
                OTLog::vError("%s line %d: Failure: Unable to set public signing key based on private string:\n%s\n",
                              __FILE__, __LINE__, strPrivate.Get());
                return false;
            }
            mapPublic.insert(std::pair<std::string, std::string>("S", strPublic.Get()));
        }
        // -------------------------------------------------
        if (false == this->ot_super::SetPublicContents(mapPublic))
        {
            OTLog::vError("%s line %d: Failure: While trying to call: ot_super::SetPublicContents(mapPublic)\n",
                          __FILE__, __LINE__); // Should never happen (it always just returns true.)
            return false;
        }
        // -------------------------------------------------
        return true; // SUCCESS! This means the input, mapPrivate, actually contained an "A" key, an "E"
        // key, and an "S" key (and nothing else) and that all three of those private keys actually loaded
        // from string form into their respective key object members. We also set the public keys in here, FYI.
    }
    // -------------------------------------------------
    return false;
}


bool OTKeyCredential::SignContract(OTContract & theContract, OTPasswordData * pPWData/*=NULL*/)
{
    return m_SigningKey.SignContract(theContract, pPWData);
}

// ***************************************************************************************

OTSubkey::OTSubkey() : ot_super()
{
    
}

OTSubkey::OTSubkey(OTCredential & theOwner) : ot_super(theOwner)
{
    
}

OTSubkey::~OTSubkey() { }

// ------------------------------

OTMasterkey::OTMasterkey() : ot_super()
{
    
}

OTMasterkey::OTMasterkey(OTCredential & theOwner) : ot_super(theOwner)
{
    
}

OTMasterkey::~OTMasterkey() { }

// ***************************************************************************************

// Contains a "master" subkey,
// and a list of "sub" subkeys signed by that master.
// Each subkey can generate its own "credential" contract,
// so OTCredential actually may include many "credentials."
// A nym has multiple OTCredentials because there may be
// several master keys.
//

// ------------------------------
const OTString & OTCredential::GetNymID() const
{
    return m_strNymID;
}
// ------------------------------

const OTString & OTCredential::GetSourceForNymID() const
{
    return m_strSourceForNymID;
}
// ------------------------------
/// This sets m_strSourceForNymID.
/// This also sets m_strNymID, which is always a hash of strSourceForNymID.
///
void OTCredential::SetSourceForNymID(const OTString & strSourceForNymID)
{
    // --------------------------------------
    m_strSourceForNymID = strSourceForNymID;
    // --------------------------------------
    //  Now re-calculate the NymID...
    //
    m_strNymID.Release();
    OTIdentifier theTempID;
    const bool bCalculate = theTempID.CalculateDigest(m_strSourceForNymID);
    OT_ASSERT(bCalculate);
    theTempID.GetString(m_strNymID);
    // ------------------------------
    m_Masterkey.SetNymIDandSource(m_strNymID, m_strSourceForNymID); // The key in here must somehow verify against its own source.
    
    // Success! By this point, m_strSourceForNymID and m_strNymID
    // are both set.
}

// ----------------------------------

const OTString & OTCredential::GetContents() const
{
    return m_Masterkey.GetContents();
}

bool OTCredential::SetPublicContents(const mapOfStrings & mapPublic)
{
    return m_Masterkey.SetPublicContents(mapPublic);
}

bool OTCredential::SetPrivateContents(const mapOfStrings & mapPrivate)
{
    return m_Masterkey.SetPrivateContents(mapPrivate);
}

// ---------------------------------
//private
OTCredential::OTCredential() :
    m_Masterkey(*this)
{ }

void OTCredential::SetMasterCredID(const OTString & strID)
{
    m_strMasterCredID = strID;
}

const OTString & OTCredential::GetMasterCredID() const
{
    return m_strMasterCredID;
}
// ---------------------------------------------------------------------------------


// called by OTCredential::CreateMaster
bool OTCredential::SignNewMaster(OTPasswordData * pPWData/*=NULL*/)
{
    OTPasswordData thePWData("Signing new master credential... OTCredential::SignNewMaster");
    // ------------------------------------
    m_Masterkey.StoreAsPublic(); // So the version we create here only contains public keys, not private.
    const bool bSignedPublic = m_Masterkey.SignContract(m_Masterkey, NULL == pPWData ? &thePWData : pPWData);
    if (bSignedPublic)
    {
        m_Masterkey.SaveContract();
        // ***********************************************************
        // NEW MASTER CREDENTIAL ID.
        //
        // (A hash of the entire master credential contract, signed, with public keys.)
        // We save the contract first, which collects the raw contents, the signatures, etc and
        // assembles the final signed contract string. Only then do we calculate the ID, since
        // that is the string that's used to calculate that ID.
        //
        OTIdentifier theNewID;
        m_Masterkey.CalculateContractID(theNewID);
        m_Masterkey.SetIdentifier(theNewID); // Usually this will be set based on an expected value from above, then loaded from storage, and then verified against what was actually loaded (by hashing it.)
        // -------------------------------        
        // Only after m_Masterkey is signed and saved can we then calculate its
        // ID and set that ID as m_strMasterCredID.
        //
        const OTString strMasterCredID(theNewID);
        this->SetMasterCredID(strMasterCredID);  // <=== Master Credential ID is now set.
        // ***********************************************************
        // THE OFFICIAL "PUBLIC CREDENTIAL" FOR THE MASTER KEY
        // (Copied from the raw contents here into a member variable for safe-keeping.)
        // Future verifiers can hash it and the output should match the master credential ID.
        //
        OTString strPublicCredential;
        
        if (m_Masterkey.SaveContractRaw(strPublicCredential))
            m_Masterkey.SetContents(strPublicCredential); // <=== The "master public credential" string.
        else
        {
            OTLog::vError("In %s, line %d: Failed calling m_Masterkey.SaveContractRaw 1.\n",
                          __FILE__, __LINE__);
            return false;
        }
        // **********************************************************
        // THE PRIVATE KEYS
        //
        // Next, we sign / save it again, this time in its private form, and also
        // m_MasterKey.m_strContents and m_strIDsOnly will be contained within that
        // private form along with the private keys.
        //
        m_Masterkey.ReleaseSignatures(); // This time we'll sign it in private mode.
        const bool bSignedPrivate = m_Masterkey.SignContract(m_Masterkey, NULL == pPWData ? &thePWData : pPWData);
        if (bSignedPrivate)
            m_Masterkey.SaveContract();
        else
        {
            OTLog::vError("In %s, line %d: Failed trying to sign the master private credential.\n",
                          __FILE__, __LINE__);
            return false;
        }
    }
    else
    {
        OTLog::vError("In %s, line %d: Failed trying to sign the master public credential.\n",
                      __FILE__, __LINE__);
        return false;
    }
    // ------------------------------------
    return true;
}

// ---------------------------------------------------------------------------------

//

bool OTCredential::SignNewSubcredential(OTSubcredential & theSubCred, OTIdentifier & theSubCredID_out, OTPasswordData * pPWData/*=NULL*/)
{
    OTPasswordData thePWData("Signing new subcredential... OTCredential::SignNewSubcredential");
    // ------------------------------------
    // First, we store the subcredential itself with its basic info.
    // This version is signed with the Masterkey. Then we save a copy of it
    // in a member variable for safe-keeping, m_strMasterSigned. Next, we
    // save a "public" version of the subcredential (the official version)
    // which will include m_strMasterSigned inside it, and be signed by the
    // subkey. This version may not need to duplicate all that data, especially
    // if we end up just having to verify it twice as a result. So I might have
    // the public version be sparse (other than including the master signed version,
    // and being signed by the subkey.)
    // Though with many subcredentials, there will ONLY be the master-signed version,
    // and that WILL be the public version. Only with subkeys will that be different!
    //
    OTSubkey * pSubkey   = dynamic_cast<OTSubkey *>(&theSubCred);
    const bool bIsSubkey = (NULL != pSubkey); // It's not just any subcredential -- it's a subkey!
    // --------------------------------------------------------------
    if (!bIsSubkey) // If it's not a subkey, but rather, a normal subcredential with no keys, then it doesn't need to contain a
        pSubkey->SetMasterSigned(OTString("")); // "master signed" version, since the entire subcredential will already be master signed, since there's no subkey to sign in that case.
    // ------------------------
    // ELSE It's a subkey...
    else // Subkeys must be self-signed, and must contain a master-signed version of themselves where the data is actually stored.
    {
        // ***********************************************************
        pSubkey->StoreAsMasterSigned(); // So the version we create here only contains public keys, not private. (And so it won't include
                                        // the "master signed" version in what it stores, since that's what we're creating now.)

        const bool bMasterSigned = m_Masterkey.SignContract(*pSubkey, NULL == pPWData ? &thePWData : pPWData);
        if (!bMasterSigned)
        {
            OTLog::vError("In %s, line %d: Failed calling m_Masterkey.SignContract(*pSubkey) after StoreAsMasterSigned.\n",
                          __FILE__, __LINE__);
            return false;
        }
        else
        {
            pSubkey->SaveContract();
            // ------------------------------------
            // Make a copy of the "master signed" version of the public subcredential.
            //
            OTString strMasterSigned;
            
            if (pSubkey->SaveContractRaw(strMasterSigned)) // <=== The "master signed" version of the "public credential" string. Captured here
                pSubkey->SetMasterSigned(strMasterSigned); // so that the (subkey-signed) public version of the subcredential will contain it.
            else
            {
                OTLog::vError("In %s, line %d: Failed calling pSubkey->SaveContractRaw 1.\n",
                              __FILE__, __LINE__);
                return false;
            }
        }
        // --------------------------
        pSubkey->ReleaseSignatures();
    }
    // ***********************************************************
    theSubCred.StoreAsPublic(); // So the version we create here only contains public keys, not private.
    
    // Here, dynamic cast theSubCred to a subkey and if successful, use it to sign itself.
    // Otherwise, sign it with the master. (If it's a real subkey, then it will contain the
    // master-signed version, and it will be signed with itself, its own subkey. Whereas if
    // it's a subcredential that is NOT a subkey, such as a Google Authenticator or some other
    // 3rd-party authentication, then it will HAVE no key to sign itself with, since its primary
    // purpose in that case is to provide some OTHER authentication info INSTEAD of a key.
    // So in that case, it must be signed by the master.)
    //
    bool bSignedPublic = false;
    
    if (bIsSubkey) // If it's a subkey, its keys are already generated by the time we got here. So use it to sign its own public version.
        bSignedPublic = pSubkey->   SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
    else // It's not a subkey, but some other conventional subcredential. So we sign with master key, since that's all we've got.
        bSignedPublic = m_Masterkey.SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
    // -----------------
    if (!bSignedPublic)
    {
        OTLog::vError("In %s, line %d: Failed trying to sign the public subcredential or subkey.\n",
                      __FILE__, __LINE__);
        return false;
    }
    else
    {
        theSubCred.SaveContract();
        // ***********************************************************
        // NEW SUB-CREDENTIAL ID.
        //
        // (A hash of the entire public subcredential contract.)
        // We save the contract first, which collects the raw contents, the signatures, etc and
        // assembles the final signed contract string. Only then do we calculate the ID, since
        // that is the string that's used to calculate that ID.
        //
        theSubCred.CalculateContractID(theSubCredID_out);
        theSubCred.SetIdentifier(theSubCredID_out);
        // ***********************************************************
        // THE OFFICIAL "PUBLIC CREDENTIAL STRING" FOR THIS NEW SUB-CREDENTIAL
        // Set it aside for safe-keeping as the official contents, hashable to form
        // the ID for this sub-credential.
        //
        OTString strPublicCredential;
        
        if (theSubCred.SaveContractRaw(strPublicCredential))
            theSubCred.SetContents(strPublicCredential); // <=== The "public credential" string aka the contents.
        else
        {
            OTLog::vError("In %s, line %d: Failed calling theSubCred.SaveContractRaw.\n",
                          __FILE__, __LINE__);
            return false;
        }
        // **********************************************************
        // CREATE THE PRIVATE FORM.
        //
        // Next, we sign / save it again, this time in its private form, and also
        // theSubCred.m_strContents will be contained within that private form,
        // along with the private keys.
        //
        theSubCred.ReleaseSignatures(); // This time we'll sign it in private mode.
        bool bSignedPrivate = false;
        
        if (bIsSubkey) // If it's a subkey, its keys are already generated by the time we got here. So use it to sign its own private version.
            bSignedPrivate = pSubkey->   SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
        else // It's not a subkey, but some other conventional subcredential. So we sign the private info with the master key, since that's all we've got.
            bSignedPrivate = m_Masterkey.SignContract(theSubCred, NULL == pPWData ? &thePWData : pPWData);
        
        if (bSignedPrivate)
            theSubCred.SaveContract();
        else
        {
            OTLog::vError("In %s, line %d: Failed trying to sign the private subcredential.\n",
                          __FILE__, __LINE__);
            return false;
        }
    }
    // ------------------------------------
    return true;
}

// ---------------------------------------------------------------------------------

bool OTCredential::GenerateMasterkey(int nBits/*=NULL*/) // CreateMaster is able to create keys from scratch (by calling this function.)
{
    return m_Masterkey.GenerateKeys(nBits);
}

// ------------------------------
// For adding subcredentials that are specifically *subkeys*. Meaning it will
// contain 3 keypairs: signing, authentication, and encryption.
//
bool OTCredential::AddNewSubkey(const int            nBits       /*=1024*/, // Ignored unless pmapPrivate is NULL
                                const mapOfStrings * pmapPrivate /*=NULL*/, // Public keys are derived from the private.
                                OTPasswordData * pPWData/*=NULL*/) // The master key will sign the subkey.
{
    OTSubkey * pSub = new OTSubkey(*this);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetNymIDandSource(this->GetNymID(), this->GetSourceForNymID()); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // -------------------------------------
    // If a map of private certs was not passed in, we're expected to
    // generate the keys ourselves.
    //
    bool bContentsReady = false;
    
    if (NULL != pmapPrivate) // Pre-generated keys were passed in for us to use,
        bContentsReady = pSub->SetPrivateContents(*pmapPrivate); // so let's set them onto the sub key.
    else
        // No keys were provided, so let's generate them ourselves...
        bContentsReady = pSub->GenerateKeys(nBits);
    // -------------------------------------
    if (!bContentsReady)
    {
        OTLog::vError("In %s, line %d: Failed trying to SetPrivateContents or GenerateKeys\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else // By this point we've set up the subkey with its NymID, the source string for that NymID,
    {    // my master credential ID, and the public and private certs for the subkey. Now let's
         // sign it...
        OTPasswordData thePWData("Signing new subkey... OTCredential::AddNewSubkey");
        OTIdentifier   theSubCredID;
        
        // SignNewSubcredential uses m_Masterkey's actual signing key to sign "pSub the contract."
        //
        if (false == this->SignNewSubcredential(*pSub, theSubCredID, NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call this->SignNewSubcredential\n",
                          __FILE__, __LINE__);
            delete pSub; pSub = NULL;
            return false;
        }
        // ---------------------------------------------
        const OTString strSubCredID(theSubCredID); // SignNewSubcredential also generates the ID.
        // -------------------------------
        // ADD IT TO THE MAP
        // Only after pSub is signed and saved can we then calculate its ID and use that ID
        // as the key in m_mapSubcredentials (with pSub being the value.)
        //
        m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubCredID.Get(), pSub));
        return true;
    }
    // -------------------------------------
    return false; // Probably unreachable.
}

// --------------------------------------------------------------------------
// For adding non-key credentials, such as for 3rd-party authentication.
//
bool OTCredential::AddNewSubcredential(const mapOfStrings & mapPrivate,
                                       const mapOfStrings & mapPublic,
                                       OTPasswordData * pPWData/*=NULL*/) // The master key will sign the subcredential.
{
    OTSubcredential * pSub = new OTSubcredential(*this);
    OT_ASSERT(NULL != pSub);
    // ----------------------
    pSub->SetNymIDandSource(m_strNymID, m_strSourceForNymID); // Set NymID and source string that hashes to it.
    pSub->SetMasterCredID  (this->GetMasterCredID());         // Set master credential ID (onto this new subcredential...)
    // -------------------------------------
    if (false == pSub->SetPublicContents(mapPublic))
    {
        OTLog::vError("In %s, line %d: Failed while calling pSub->SetPublicContents.\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else if (false == pSub->SetPrivateContents(mapPrivate))
    {
        OTLog::vError("In %s, line %d: Failed while trying to pSub->SetPrivateContents.\n",
                      __FILE__, __LINE__);
        delete pSub; pSub = NULL;
        return false;
    }
    // -------------------------------------
    else // By this point we've set up the subcredential with its NymID, the source string for that NymID,
    {    // my master credential ID, and the public and private contents for the subcredential. Let's sign
         // it...
        OTPasswordData thePWData("Signing new subcredential... OTCredential::AddNewSubcredential");
        OTIdentifier   theSubCredID;
        
        // SignNewSubcredential uses m_Masterkey's actual signing key to sign "pSub the contract."
        //
        if (false == this->SignNewSubcredential(*pSub, theSubCredID, NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call this->SignNewSubcredential\n",
                          __FILE__, __LINE__);
            delete pSub; pSub = NULL;
            return false;
        }
        // ---------------------------------------------
        const OTString strSubCredID(theSubCredID);
        // -------------------------------
        // ADD IT TO THE MAP
        // Only after pSub is signed and saved can we then calculate its ID and use that ID
        // as the key in m_mapSubcredentials (with pSub being the value.)
        //
        m_mapSubcredentials.insert(std::pair<std::string, OTSubcredential *>(strSubCredID.Get(), pSub));
        return true;
    }
    // -------------------------------------
    return false; // Probably unreachable.
}

// ---------------------------------------------------------------------------------
// After calling this, you still need to save it to disk (or not.) This function alone
// doesn't save anything to disk.
//
//static
OTCredential * OTCredential::CreateMaster(const OTString     & strSourceForNymID,
                                          const int            nBits/*=1024*/,       // Ignored unless pmapPrivate is NULL.
                                          const mapOfStrings * pmapPrivate/*=NULL*/, // If NULL, then the keys are generated in here.
                                          const mapOfStrings * pmapPublic /*=NULL*/, // In the case of key credentials, public is optional since it can already be derived from private. But not all credentials are keys...
                                          OTPasswordData * pPWData/*=NULL*/)
{
    OTCredential * pCredential = new OTCredential;
    OT_ASSERT(NULL != pCredential);
    // -------------------------------------
    pCredential->SetSourceForNymID(strSourceForNymID); // This also recalculates and sets  ** m_strNymID **
    // -------------------------------------
    // OTKeyCredential::SetPrivateContents will already set the public keys, which is why this argument is optional. But not all credentials are keys, so we must still retain the ability to explicitly set the public info. Even so, in the case of keys, private is below, so it will overwrite this.
    if ((NULL != pmapPublic) &&
        (NULL != pmapPrivate)) // You cannot pass public info in here unless you also pass private info.
    {
        if (false == pCredential->SetPublicContents(*pmapPublic))
        {
            OTLog::vError("In %s, line %d: Failed trying to call pCredential->SetPublicContents\n",
                          __FILE__, __LINE__);
            delete pCredential;
            pCredential = NULL;
            return NULL;
        }
    }
    // -------------------------------------
    // Private info must be passed in to create a credential. This saves a copy of the map, and for keys also loads the map all up into the OTKeypair objects (in the case of OTKeyCredentials anyway -- not all credentials are keys.)
    //
    bool bContentsReady = false;
    
    if (NULL != pmapPrivate) // Pre-generated keys were passed in for us to use.
        bContentsReady = pCredential->SetPrivateContents(*pmapPrivate); // So let's set them onto the master key.
    else
        // No keys were provided, so let's generate them ourselves...
        bContentsReady = pCredential->GenerateMasterkey(nBits);
    // -------------------------------------
    if (!bContentsReady)
    {
        OTLog::vError("In %s, line %d: Failed trying to SetPrivateContents or GenerateMasterkey\n",
                      __FILE__, __LINE__);
        delete pCredential;
        pCredential = NULL;
        return NULL;
    }
    else
    {
        OTPasswordData thePWData("Signing new master credential... OTCredential::CreateMaster");
        
        // Using m_Masterkey's actual signing key to sign "m_Masterkey the contract."
        //
        if (false == pCredential->SignNewMaster(NULL == pPWData ? &thePWData : pPWData))
        {
            OTLog::vError("In %s, line %d: Failed trying to call pCredential->SignNewMaster\n",
                          __FILE__, __LINE__);
            delete pCredential;
            pCredential = NULL;
            return NULL;
        }
    }
    // By this point, we have instantiated a new OTCredential, set the source string, hashed that
    // source string to get the NymID for this credential, and set the public and private info for
    // this credential (each a map of strings.) Since pCredential->m_MasterKey is derived from
    // OTKeyCredential, it also loaded up the 3 keypairs (authentication, encryption, and signing.)
    // Then we signed that master key with itself, with its signing key. (It's also an OTContract,
    // so it can be signed.) This also calculated the new master credential ID, and called
    // pCredential->SetMasterCredID. That is, the OTCredential's "master credential ID" is formed
    // as a hash of the signed contract that is its OTMasterkey.
    // BUT!!! We don't want to use a hash of the private key information, since others cannot verify
    // the hash without seeing our private key. We want OTMasterkey to create an 'official' signed
    // public version of itself, minus private keys, which is what can be sent to servers and to
    // other users, and which can be hashed to form the master credential ID (and verified later.)
    // ...Which is exactly what it does. Inside pCredential->SignNewMaster, a public version is created
    // and signed, and set onto that masterkey as m_strContents. It's then re-signed as the private
    // version, which contains m_strContents in encoded form, along with the private keys.
    //
    return pCredential;
}

// ----------------------------------

OTCredential::~OTCredential()
{
    // ---------------------------
	while (!m_mapSubcredentials.empty())
	{
		OTSubcredential * pSub = m_mapSubcredentials.begin()->second;
		OT_ASSERT(NULL != pSub);
		// -----------
		delete pSub;
		pSub = NULL;
        // -----------
		m_mapSubcredentials.erase(m_mapSubcredentials.begin());
	} // while
    // ---------------------------
}

// ------------------------------------------------





















// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------





















