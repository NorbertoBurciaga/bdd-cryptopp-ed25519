/*==================================================================================================
 *
 *  Description:  Key pair generation and storage Cucumber-cpp Steps
 *      Created:  2019-02-20
 *
 *       Author:  Norberto Burciaga
 * Organization:  NBsis <http://www.nbsis.com>
 *
 * All rights reserved Norberto Burciaga © 2019
 *==================================================================================================
 */

#ifndef TESTS_FEATURES_STEP_DEFINITIONS_SIGNATURESTEPS_H_
#define TESTS_FEATURES_STEP_DEFINITIONS_SIGNATURESTEPS_H_
#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <cryptopp/osrng.h>
#include <cryptopp/xed25519.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>


using cucumber::ScenarioScope;
using namespace std;

class SignatureSteps {
public:
	string privateKeyFilename;
	string publicKeyFilename;
	CryptoPP::ed25519::Signer signer;
	CryptoPP::ed25519::Verifier *verifier;
};

#endif /* TESTS_FEATURES_STEP_DEFINITIONS_SIGNATURESTEPS_H_ */
