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
	CryptoPP::AutoSeededRandomPool rnd;

	CryptoPP::ByteQueue queue;

	try {
        context->privateKey.GenerateRandom(rnd, CryptoPP::g_nullNameValuePairs);

        context->privateKey.Save(queue);
        CryptoPP::FileSink file(context->privateKeyFilename.c_str());
        queue.CopyTo(file);
        file.MessageEnd();

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
	CryptoPP::ByteQueue queue;
	try {
		CryptoPP::FileSource file(context->privateKeyFilename.c_str(), true /*pumpAll*/);

		file.TransferTo(queue);
		queue.MessageEnd();
		context->privateKey.Load(queue);
	} catch(const CryptoPP::Exception& e) {
		cerr << "Cryptographic Error: " << e.what() << endl;
		ASSERT_TRUE(false);
	} catch(const runtime_error& e) {
		cerr << "Runtime Error: " << e.what() << endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}

THEN("^an ed25519 public key should be generated and stored in base64 format$") {
	ScenarioScope<KeySteps> context;
    CryptoPP::Base64Encoder pubbase64;

	try {
		context->privateKey.MakePublicKey(context->publicKey);
		context->publicKey.DEREncode(pubbase64);
		CryptoPP::FileSink pubfile(context->publicKeyFilename.c_str());
		pubbase64.CopyTo(pubfile);
		pubfile.MessageEnd();
	} catch(const CryptoPP::Exception& e) {
		std::cerr << "Crypto Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	} catch(const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}
