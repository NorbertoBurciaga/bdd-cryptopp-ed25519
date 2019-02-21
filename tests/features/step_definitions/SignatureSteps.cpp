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
#include "SignatureSteps.h"

GIVEN("^a private key \"([^\"]*)\"$") {
	ScenarioScope<SignatureSteps> context;
	CryptoPP::AutoSeededRandomPool prng;

	REGEX_PARAM(string, filename);
	context->privateKeyFilename = filename;

	// Load the private key from a file
	CryptoPP::FileSource fs1(context->privateKeyFilename.c_str(), true);
	context->signer.AccessPrivateKey().Load(fs1);

	bool valid = context->signer.GetPrivateKey().Validate(prng, 3);
	ASSERT_TRUE(valid);
}

WHEN("^it is required to sign a message$") {
	ScenarioScope<SignatureSteps> context;

	try {
		context->publicKeyFilename = "public.key";
		CryptoPP::Base64Encoder encoder(new CryptoPP::FileSink(context->publicKeyFilename.c_str()),false);

		context->verifier = new CryptoPP::ed25519::Verifier(context->signer);
		context->verifier->GetPublicKey().Save(encoder);
	} catch(const CryptoPP::Exception& e) {
		std::cerr << "Cryptographic Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	} catch(const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}

THEN("^a signature for ([^\"]*) should be created$") {
	ScenarioScope<SignatureSteps> context;
	CryptoPP::AutoSeededRandomPool prng;
	string signature;

	REGEX_PARAM(string, message);

	CryptoPP::StringSource(message, true,
		new CryptoPP::SignerFilter(prng, context->signer,
			new CryptoPP::StringSink(signature)
		)
	);

	CryptoPP::Base64Encoder encoder(new CryptoPP::FileSink(std::cout),false);

	cout << endl << "Message: " << message << endl << "Signature: " << endl;
	CryptoPP::StringSource(signature, true, new CryptoPP::Redirector(encoder));
	cout << endl << "Public Key:" << endl;

	CryptoPP::Base64Encoder encoder1(new CryptoPP::FileSink(std::cout),false);
	context->verifier->GetPublicKey().Save(encoder1);
	std::cout << "\n" << std::endl;
}
