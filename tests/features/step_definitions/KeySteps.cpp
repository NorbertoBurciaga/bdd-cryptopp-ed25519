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
#include "KeySteps.h"

GIVEN("^the filename \"([^\"]*)\" to store the private key$") {
	ScenarioScope<KeySteps> context;

	REGEX_PARAM(string, filename);
	context->privateKeyFilename = filename;
}

WHEN("^the application starts$") {
}

THEN("^an ed25519 private key should be created and stored in DER format$") {
	ScenarioScope<KeySteps> context;
	CryptoPP::AutoSeededRandomPool prng;

	try {
		context->signer.AccessPrivateKey().GenerateRandom(prng);
		CryptoPP::FileSink fs1(context->privateKeyFilename.c_str());
		context->signer.GetPrivateKey().Save(fs1);

	} catch(const CryptoPP::Exception& e) {
		cerr << "Cryptographic Error: " << e.what() << endl;
		ASSERT_TRUE(false);
	} catch(const runtime_error& e) {
		cerr << "Runtime Error: " << e.what() << endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}

GIVEN("^the private key stored in \"([^\"]*)\"$") {
	ScenarioScope<KeySteps> context;

	REGEX_PARAM(string, filename);
	context->privateKeyFilename = filename;
}

GIVEN("^the filename \"([^\"]*)\" to store the public key$") {
	ScenarioScope<KeySteps> context;

	REGEX_PARAM(string, filename);
	context->publicKeyFilename = filename;
}

WHEN("^loading the private key$") {
	ScenarioScope<KeySteps> context;
	CryptoPP::AutoSeededRandomPool prng;

	CryptoPP::FileSource fs1(context->privateKeyFilename.c_str(), true);
	context->signer.AccessPrivateKey().Load(fs1);

	bool valid = context->signer.GetPrivateKey().Validate(prng, 3);

	ASSERT_TRUE(valid);
}

THEN("^an ed25519 public key should be generated and stored in base64 format$") {
	ScenarioScope<KeySteps> context;
	CryptoPP::Base64Encoder encoder(new CryptoPP::FileSink(context->publicKeyFilename.c_str()),false /*line breaks*/);

	try {
		context->verifier = new CryptoPP::ed25519::Verifier(context->signer);

		context->verifier->GetPublicKey().Save(encoder);
		encoder.MessageEnd();

	} catch(const CryptoPP::Exception& e) {
		std::cerr << "Crypto Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	} catch(const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}
