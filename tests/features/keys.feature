# language: en

Feature: Generate and store ed25519 keys

Scenario: Generate ed25519 private key and store it in DER format
	Given the filename "private.der" to store the private key
	When the application starts
	Then an ed25519 private key should be created and stored in DER format
	
Scenario: Load a private key to generate the corresponding public key
	Given the private key stored in "myprivatekey.der"
	And the filename "public.key" to store the public key
	When loading the private key
	Then an ed25519 public key should be generated and stored in base64 format