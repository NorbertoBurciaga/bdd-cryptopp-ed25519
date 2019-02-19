# language: en

Feature: Generate and store ed25519 keys

Scenario: Generate ed25519 private key and store it in DER format
	Given the filename "private.der" to store the private key
	When the application starts
	Then a ed25519 private key should be created and stored in DER format