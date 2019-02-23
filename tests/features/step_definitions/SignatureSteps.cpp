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
		context->verifier = new CryptoPP::ed25519::Verifier(context->signer);

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
	bool valid;

	REGEX_PARAM(string, message);

	// Sign message
	CryptoPP::StringSource(message, true,
		new CryptoPP::SignerFilter(prng, context->signer,
			new CryptoPP::StringSink(signature)
		)
	);

	// display messge, and signature base64 encoded
/*	CryptoPP::Base64Encoder encoder(new CryptoPP::FileSink(std::cout),false);
	cout << endl << "Message: " << message << endl << "Signature: " << endl;
	CryptoPP::StringSource(signature, true, new CryptoPP::Redirector(encoder));
	cout << endl << "Public Key:" << endl;
	CryptoPP::Base64Encoder encoder1(new CryptoPP::FileSink(std::cout),false);
	context->verifier->GetPublicKey().Save(encoder1);
	std::cout << "\n" << std::endl;*/

	// Verify signature of the message
	CryptoPP::StringSource(signature+message, true,
		new CryptoPP::SignatureVerificationFilter(*(context->verifier),
			new CryptoPP::ArraySink((CryptoPP::byte*)&valid, sizeof(valid))
		)
	);
	ASSERT_TRUE(valid);
}

GIVEN("^a message with its signature$") {
}


WHEN("^it is required to verify the signature of a message$") {
}


THEN("^verify the ([^\"]*) of the ([^\"]*) using the ([^\"]*) provided$") {
	ScenarioScope<SignatureSteps> context;
	CryptoPP::AutoSeededRandomPool prng;
	bool valid;
	string signatureDecoded;

	REGEX_PARAM(string, signature);
	REGEX_PARAM(string, message);
	REGEX_PARAM(string, publicKey);

	try {
		CryptoPP::StringSource ssPublicKeyDecoded(publicKey, true, new CryptoPP::Base64Decoder);

		CryptoPP::StringSource ssSignatureDecoded(signature, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(signatureDecoded)));

		context->verifier = new CryptoPP::ed25519::Verifier();
		context->verifier->AccessPublicKey().Load(ssPublicKeyDecoded);

		valid = context->verifier->GetPublicKey().Validate(prng, 3);
		if (valid == false)
		    throw std::runtime_error("Invalid public key");

		// Verify signature of the message
		CryptoPP::StringSource(signatureDecoded+message, true,
			new CryptoPP::SignatureVerificationFilter(*(context->verifier),
				new CryptoPP::ArraySink((CryptoPP::byte*)&valid, sizeof(valid))
			)
		);
		if (valid == false)
			throw std::runtime_error("This message is not signed with this signature");

	} catch(const CryptoPP::Exception& e) {
		std::cerr << "Cryptographic Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	} catch(const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(true);
}
