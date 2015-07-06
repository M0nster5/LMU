/* compile with
 * g++-5 --std=c++11 -fdiagnostics-color=auto -mtune=native -march=native -D_GLIBCXX_USE_CXX11_ABI=0 -c vector2test.cc -o vector2test.o
 * g++-5 vector2test.o ../vector2.o -lboost_unit_test_framework -o test_vec2
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN // generate a main function that performs the tests below
#include <boost/test/unit_test.hpp>

#include <limits>

typedef double Float;

namespace {

Vector2 abs(Vector2::ConstArgType v) {
	return Vector2(std::abs(v.x), std::abs(v.y));
}

bool operator<(Vector2::ConstArgType v, const Float e)
{
	return v.x < e && v.y < e;
}

bool operator==(Vector2::ConstArgType v1, Vector2::ConstArgType v2) {
	Vector2 tmp(abs(v1 - v2)), v1a(abs(v1)), v2a(abs(v2));
	const Float eps = std::numeric_limits<Float>::epsilon();
	return tmp / v1a < eps && tmp / v2a < eps;
}

constexpr Float tol = 0.0001;

} /* unnamed namespace */


BOOST_AUTO_TEST_SUITE(Test_Vector2);

BOOST_AUTO_TEST_CASE(Constructor)
{
	/* explicit constructor with 3 args */
	Vector2 v1(1, -2);
	BOOST_CHECK_CLOSE(v1.x, (Float)1, tol);
	BOOST_CHECK_CLOSE(v1.y, (Float)-2, tol);

	/* explicit constructor with 1 arg */
	BOOST_CHECK(Vector2(3) == Vector2(3, 3));
}

BOOST_AUTO_TEST_CASE(Access)
{
	/* getter access */
	Vector2 v1(3.1, -5);
	BOOST_CHECK_CLOSE(v1[0], 3.1, tol);
	BOOST_CHECK_CLOSE(v1[1], -5, tol);

	/* setter access */
	v1[0] = 2.0; v1[1] = 2.1;
	BOOST_CHECK_CLOSE(v1.x, 2.0, tol);
	BOOST_CHECK_CLOSE(v1.y, 2.1, tol);

	v1.set_all(7.);
	BOOST_CHECK(v1 == Vector2(7.));
}

BOOST_AUTO_TEST_CASE(Addition)
{
	Vector2 v1(1, 3), v2(.3, .03), res(1.3, 3.03);

	/* addition assignment */
	Vector2 tmp(v1);
	tmp += v2;
	BOOST_CHECK(tmp == res);

	/* addition */
	BOOST_CHECK(v1 + v2 == res);
	/* commutativity */
	BOOST_CHECK(v2 + v1 == res);

	/* associativity */
	Vector2 v3(10, 100), res2(11.3, 103.03);
	BOOST_CHECK(v1 + (v2 + v3) == res2);
	BOOST_CHECK((v1 + v2) + v3 == res2);
}

BOOST_AUTO_TEST_CASE(Subtraction)
{
	Vector2 v1(1, 3), v2(.3, .03), res(.7, 2.97);

	/* subtraction assignment */
	Vector2 tmp(v1);
	tmp -= v2;
	BOOST_CHECK(tmp == res);

	/* subtraction */
	BOOST_CHECK(v1 - v2 == res);
	/* commutativity */
	BOOST_CHECK(v2 - v1 == Vector2(-.7, -2.97));

	/* neutral element */
	BOOST_CHECK(v1 - Vector2(.0) == v1);

	/* associativity */
	Vector2 v3(10, 100);
	BOOST_CHECK(v1 - (v2 + v3) == v1 - v2 - v3);
}

BOOST_AUTO_TEST_CASE(Multiplication)
{
	Vector2 v1(1, 3), v2(.3, .02), v3(10, 100);

	/* multiplication assignment */
	Vector2 tmp(v1);
	tmp *= v1;
	BOOST_CHECK(tmp == Vector2(1, 9));

	/* multiplication */
	BOOST_CHECK(v2 * v3 == Vector2(3, 2));

	/* neutral element */
	BOOST_CHECK(v1 * Vector2(1) == v1);

	/* associativity */
	BOOST_CHECK(v1 * (v2 * v3) == (v1 * v2) * v3);
}

BOOST_AUTO_TEST_CASE(ScalarMultiplication)
{
	Vector2 v1(1, 3), v2(.3, .02);

	/* multiplication assignment */
	Vector2 tmp(v1);
	tmp *= 7;
	BOOST_CHECK(tmp == Vector2(7, 21));

	/* multiplication */
	tmp = v2 * 7;
	BOOST_CHECK(tmp == Vector2(2.1, .14));
}

BOOST_AUTO_TEST_CASE(Division)
{
	Vector2 v1(1, 3), v2(.3, .02), v3(10, 100);

	/* division assignment */
	Vector2 tmp(v1);
	tmp /= v3;
	BOOST_CHECK(tmp == Vector2(.1, .03));

	/* division */
	BOOST_CHECK(v1 / v3 == Vector2(.1, .03));

	/* neutral element */
	BOOST_CHECK(v1 * Vector2(1) == v1);

	/* associativity */
	BOOST_CHECK(v1 / (v2 * v3) == (v1 / v2) / v3);
}

BOOST_AUTO_TEST_CASE(ScalarDivision)
{
	Vector2 v1(9, 3);

	/* multiplication assignment */
	Vector2 tmp(v1);
	tmp /= 3;
	BOOST_CHECK(tmp == Vector2(3, 1));

	/* multiplication */
	tmp = v1 / 3;
	BOOST_CHECK(tmp == Vector2(3, 1));
}

BOOST_AUTO_TEST_CASE(Dot)
{
	Vector2 v1(2, 3), v2(7, 11);
	const Float res = 47;

	BOOST_CHECK_CLOSE(v1.dot(v2), res, tol);
	BOOST_CHECK_CLOSE(v2.dot(v1), res, tol);
}

BOOST_AUTO_TEST_CASE(Cross)
{
	Vector2 v1(2, 3), v2(7, 11);

	BOOST_CHECK_CLOSE(v1.cross(v2), 1, tol);
	BOOST_CHECK_CLOSE(v2.cross(v1), -1, tol);
}

BOOST_AUTO_TEST_CASE(Abs)
{
	Vector2 v1(2, -5);

	BOOST_CHECK_CLOSE(v1.abs2(), 29., tol);
	BOOST_CHECK_CLOSE(v1.abs(), std::sqrt(29.), tol);
}

BOOST_AUTO_TEST_CASE(MaxNorm)
{
	Vector2 v1(5, 100), v2(-1e7, 1e7);

	BOOST_CHECK_CLOSE(v1.maxnorm(), 100, tol);
	BOOST_CHECK_CLOSE(v2.maxnorm(), 1e7, tol);
}

BOOST_AUTO_TEST_CASE(Axpy)
{
	const Vector2 x(1, 2), y(.3, .02);
	Vector2 tmp;

	tmp = x;
	tmp.axpy(1, y);
	BOOST_CHECK(tmp == Vector2(1.3, 2.02));

	tmp = x;
	tmp.axpy(-1, y);
	BOOST_CHECK(tmp == Vector2(.7, 1.98));

	tmp = x;
	tmp.axpy(10, y);
	BOOST_CHECK(tmp == Vector2(4, 2.2));
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES(Normalize, 1);
BOOST_AUTO_TEST_CASE(Normalize)
{
	Vector2 v1(3, 4), v2(0);

	v1.normalize();
	BOOST_CHECK(v1 == Vector2(.6, .8));

	v2.normalize();
	BOOST_CHECK_MESSAGE(v2 == Vector2(0), "normalized null-vector not zero: " << v2);
}

BOOST_AUTO_TEST_SUITE_END();
