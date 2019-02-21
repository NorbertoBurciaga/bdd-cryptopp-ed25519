# language: en
Feature: sign messages and verify signatures

Scenario Outline: Sign messages
	Given a private key "myprivatekey.der"
	When it is required to sign a message
	Then a signature for <message> should be created
	Examples:
	| message                                        |
	| Hello World!                                   |
	| This is another message                        |
	| Luke...I am...your father......Noooohhhh!!     |
	| Yoda said, Do or do not. There is no try.      |
	
#Scenario Outline: Verify signatures
#	Given a <message>
#	And a message <signature>
#	And a public key
#	When it is required to verify the signature of a message
#	Then encoding the extract of a message with the public key should verify the signature
#	Examples:
#	| message                                    | signature                                                                                | public_key                                               |
#	| Hello World!                               | Wco3F+W0r59dv2jigjt7RvZYHmoI/ncwkryTV3NtsDQOpw8aQcJK1XEWjG1tEapg9Ato7we8n+PFXk+warb3CQ== | MCowBQYDK2VwAyEAMIln+WHCa/M/HUjOjiSDdICkfmLpgV418ae3I2Tg |
#	| This is another message                    | s4NxocipG2rzkrz9N/xi6tNKhr657pRMbbA05bz9l/gCCKT34Nc4tBOGeoE1PDbNMROwfwIvzAdrSf2FraM2Aw== | MCowBQYDK2VwAyEAMIln+WHCa/M/HUjOjiSDdICkfmLpgV418ae3I2Tg |
#	| Luke...I am...your father......Noooohhhh!! | istSmvPZ0FFaJCOQDEmDrWKTI4qL0Ez8rtmQvmJ7+u9BuzXIzPsrF+f8iAoPLXSySQkryAQwW+BsDLV6I58jCw== | MCowBQYDK2VwAyEAMIln+WHCa/M/HUjOjiSDdICkfmLpgV418ae3I2Tg |
#	| Yoda said, Do or do not. There is no try.  | OWdLCp9iljSKp34sDtl23UDUUX75CYNmR17nIMbzhJXAYTCJW/BWqXofjZf1oBshhKEUtCynOZXlZT8WRhV3AA== | MCowBQYDK2VwAyEAMIln+WHCa/M/HUjOjiSDdICkfmLpgV418ae3I2Tg |
