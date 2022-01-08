module Math;
using namespace Math;
Rational::Rational() : nom(0), denom(1) {};
Rational::Rational(int n, int d) {
	const int gcd = Math::FindGreatestCommonDivisor(n, d);
	const int sign = ((n * d) > 0) ? 1 : -1;
	nom = abs(n / gcd) * sign;
	denom = abs(d / gcd);
};
Rational::Rational(int n) : nom(n), denom(1) {};

int Rational::Nominator() const {
	return nom;
};
int Rational::Denominator() const {
	return denom;
}

Rational Math::operator + (const Rational& a, const Rational& b) {
	const int denom_lcm = Math::FindLeastCommonMultiple(a.Denominator(), b.Denominator());
	return Rational((a.Nominator() * denom_lcm / a.Denominator()) + (b.Nominator() * denom_lcm / b.Denominator()), denom_lcm);
};

Rational Math::operator * (const Rational& a, const Rational& b) {
	return Rational(a.Nominator() * b.Nominator(), a.Denominator() * b.Denominator());
}

Rational::operator double() const {
	return ((double)nom) / ((double)denom);
}

Rational Rational::operator-() {
	return Rational(-nom, denom);
};

Rational& Rational::operator++() {
	nom += denom;
	return *this;
};
Rational Rational::operator++(int) {
	Rational old = *this;
	nom += denom;
	return old;
};
Rational& Rational::operator--() {
	nom -= denom;
	return *this;
};
Rational Rational::operator--(int) {
	Rational old = *this;
	nom -= denom;
	return old;
};
Rational Math::operator - (const Rational& a, const Rational& b) {
	const int denom_lcm = Math::FindLeastCommonMultiple(a.Denominator(), b.Denominator());
	return Rational((a.Nominator() * denom_lcm / a.Denominator()) - (b.Nominator() * denom_lcm / b.Denominator()), denom_lcm);
};
Rational Math::operator / (const Rational& a, const Rational& b) {
	return Rational(a.Nominator() * b.Denominator(), a.Denominator() * b.Nominator());
};

bool Rational::operator ==(Rational x) {
	return (this->Nominator() == x.Nominator()) && (this->Denominator() == x.Denominator());
};
bool Rational::operator !=(Rational x) {
	return (this->Nominator() != x.Nominator()) || (this->Denominator() != x.Denominator());
};

bool Rational::operator >(Rational x) {
	const int lcm = Math::FindLeastCommonMultiple(this->Denominator(), x.Denominator());
	const int a_nom = this->Nominator() * lcm / this->Denominator();
	const int b_nom = x.Nominator() * lcm / x.Denominator();

	return a_nom > b_nom;
};
bool Rational::operator <(Rational x) {
	const int lcm = Math::FindLeastCommonMultiple(this->Denominator(), x.Denominator());
	const int a_nom = this->Nominator() * lcm / this->Denominator();
	const int b_nom = x.Nominator() * lcm / x.Denominator();

	return a_nom < b_nom;
};

bool Rational::operator >=(Rational x) {
	return ((*this) == x) || ((*this) > x);
};
bool Rational::operator <=(Rational x) {
	return ((*this) == x) || ((*this) < x);
};

Rational& Rational::operator+=(const Rational& a) {
	const int new_denom = Math::FindLeastCommonMultiple(this->Denominator(), a.Denominator());
	const int new_nom = (this->Nominator() * new_denom / this->Denominator()) + (a.Nominator() * new_denom / a.Denominator());

	const int gcd = Math::FindGreatestCommonDivisor(new_nom, new_denom);
	const int sign = ((new_nom * new_denom) > 0) ? 1 : -1;
	nom = abs(new_nom / gcd) * sign;
	denom = abs(new_denom / gcd);

	return *this;
};
Rational& Rational::operator-=(const Rational& a) {
	const int new_denom = Math::FindLeastCommonMultiple(this->Denominator(), a.Denominator());
	const int new_nom = (this->Nominator() * new_denom / this->Denominator()) - (a.Nominator() * new_denom / a.Denominator());

	const int gcd = Math::FindGreatestCommonDivisor(new_nom, new_denom);
	const int sign = ((new_nom * new_denom) > 0) ? 1 : -1;
	nom = abs(new_nom / gcd) * sign;
	denom = abs(new_denom / gcd);

	return *this;
};
Rational& Rational::operator*=(const Rational& a) {
	const int new_nom = this->Nominator() * a.Nominator();
	const int new_denom = this->Denominator() * a.Denominator();
	const int gcd = Math::FindGreatestCommonDivisor(new_nom, new_denom);

	nom = new_nom / gcd;
	denom = new_denom / gcd;

	return *this;
};
Rational& Rational::operator/=(const Rational& a) {
	const int new_nom = this->Nominator() * a.Denominator();
	const int new_denom = this->Denominator() * a.Nominator();
	const int gcd = Math::FindGreatestCommonDivisor(new_nom, new_denom);

	nom = new_nom / gcd;
	denom = new_denom / gcd;

	return *this;
};

int Math::FindGreatestCommonDivisor(int a, int b) {
	a = abs(a);
	b = abs(b);
	int next;
	do {
		next = a % b;
		a = b;
		b = next;
	} while (next != 0);
	return a;
};

int Math::FindLeastCommonMultiple(int a, int b) {
	return abs(a * b) / Math::FindGreatestCommonDivisor(a, b);
};