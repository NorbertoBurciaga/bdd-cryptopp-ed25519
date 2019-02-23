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
	
Scenario Outline: Verify signatures
	Given a message with its signature
	When it is required to verify the signature of a message
	Then verify the <signature> of the <message> using the <public_key> provided
	Examples:
	| message                                    | signature                                                                                | public_key                                                   |
	| Hello World!                               | Wco3F+W0r59dv2jigjt7RvZYHmoI/ncwkryTV3NtsDQOpw8aQcJK1XEWjG1tEapg9Ato7we8n+PFXk+warb3CQ== | MCowBQYDK2VwAyEAMIln+WHCa/M/HUjOjiSDdICkfmLpgV418ae3I2TgdIQ= |
	| This is another message                    | T5ui0OP7ynwHzIAvNVTF72sAStGRsQ8TJcTUKhr1mzv7kJvPpH3+Sp59zzMfqoJWZeXknCwe+x1qoP3Dxz66CQ== | MCowBQYDK2VwAyEAE3SEBBcbpc/UMuKnJVOY9yladFlarHoKgga7Mv9i8wc= |
	| Luke...I am...your father......Noooohhhh!! | 69yppm2lB2KzQyJqW03gRS0G+ldubAe3BJVJAp8nxTKiezsUWv6eqdiytMVPzvXEQ6m9K9s6Hohj6qDn66GQAA== | MCowBQYDK2VwAyEAnidHjUYZGsdCYmUSnfRDie1egnW/4cNa2YjscumtdBo= |
	| Yoda said, Do or do not. There is no try.  | 5ke0fcF0TfZ2DsPEf/X2iVOZ6CjXg0X5dsplEJlBV5Kak9+whXIPyuWggHyPceNNDZ80MwuK+mhgtUaKBMd8Bg== | MCowBQYDK2VwAyEA3fqIDX1hAFFpAsNKpcOLqf+JJU7TLjTyIj/XNZbPs4Q= |
