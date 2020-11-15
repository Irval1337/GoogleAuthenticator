#pragma once
using namespace System;
ref class App {
public:
	String^ QR;
	String^ Login;
	String^ Secret;
	String^ Site;
	String^ Code;
};
ref class User {
public:
	String^ Id;
	String^ Username;
	String^ Email;
	String^ Password;
	array<App^>^ Applications;
};