/*==================================================================================================
 *
 *  Description:  Key pair generation and storage Cucumber-cpp Steps
 *      Created:  2019-02-19
 *
 *       Author:  Norberto Burciaga
 * Organization:  NBsis <http://www.nbsis.com>
 *
 * All rights reserved Norberto Burciaga © 2019
 *==================================================================================================
 */
#ifndef TESTS_FEATURES_STEP_DEFINITIONS_KEYSTEPS_H_
#define TESTS_FEATURES_STEP_DEFINITIONS_KEYSTEPS_H_

#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <cryptopp/osrng.h>
#include <cryptopp/xed25519.h>
#include <cryptopp/files.h>


using cucumber::ScenarioScope;
using namespace std;

class KeySteps {
public:
	string privateKeyFilename;
	CryptoPP::ed25519PrivateKey privateKey;
};

#endif /* TESTS_FEATURES_STEP_DEFINITIONS_KEYSTEPS_H_ */
