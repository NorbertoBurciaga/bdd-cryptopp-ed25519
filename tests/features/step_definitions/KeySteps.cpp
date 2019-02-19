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

THEN("^a ed25519 private key should be created and stored in DER format$") {
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
