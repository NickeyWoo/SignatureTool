#include <complex>
#include "Line.h"
using namespace std;

// See http://www.deqnotes.net/acmicpc/2d_geometry/lines

namespace Line
{
	// ���e����덷��
#define EPS (1e-10)
	// 2�̃X�J���[�����������ǂ���
#define EQ(a,b) (abs((a)-(b)) < EPS)
	// 2�̃x�N�g�������������ǂ���
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

	// �x�N�g��a�̐�Βl�����߂�
	double length(const P& a) {
		return abs(a);
	}

	// 2�_a,b�Ԃ̋��������߂�
	double distance(const P& a, const P& b) {
		return abs(a-b);
	}

	// �x�N�g��a�̒P�ʃx�N�g�������߂�
	P unit_vector(const P& a) {
		return a / abs(a);
	}

	// �x�N�g��a�̖@���x�N�g��n1,n2�����߂�
	pair<P, P> normal(const P& a) {
		P n1 = a * P(0, 1);
		P n2 = a * P(0, -1);
		return pair<P, P>(n1, n2);
	}

	// �x�N�g��a�̒P�ʖ@���x�N�g��un1,un2�����߂�
	pair<P, P> unit_normal(const P& a) {
		P un1 = (a * P(0, +1)) / abs(a);
		P un2 = (a * P(0, -1)) / abs(a);
		return pair<P, P>(un1, un2);
	}

	// ���� (dot product) : a�Eb = |a||b|cos��
	double dot(const P& a, const P& b) {
		return (a.real() * b.real() + a.imag() * b.imag());
	}

	// �O�� (cross product) : a�~b = |a||b|sin��
	double cross(const P& a, const P& b) {
		return (a.real() * b.imag() - a.imag() * b.real());
	}

	// 2�����̒��𔻒� : a��b <=> dot(a, b) = 0
	bool is_orthogonal(const P& a1, const P& a2, const P& b1, const P& b2) {
		return EQ( dot(a1-a2, b1-b2), 0.0 );
	}

	// 2�����̕��s���� : a//b <=> cross(a, b) = 0
	bool is_parallel(const P& a1, const P& a2, const P& b1, const P& b2) {
		return EQ( cross(a1-a2, b1-b2), 0.0 );
	}

	//// �_c������a,b��ɂ��邩�Ȃ���
	//bool is_point_on_line(const P& a, const P& b, const P& c) {
	//	return EQ( cross(b-a, c-a), 0.0 );
	//}

	// �_c������a,b��ɂ��邩�Ȃ���(1)
	bool is_point_on_line(const P& a, const P& b, const P& c) {
		return EQ( cross(b-a, c-a), 0.0 ) &&
			(dot(b-a, c-a) > -EPS) &&
			(dot(a-b, c-b) > -EPS);
	}

	// �_c������a,b��ɂ��邩�Ȃ���(2)
	//bool is_point_on_line(const P& a, const P& b, const P& c) {
	//	// |a-c| + |c-b| <= |a-b| �Ȃ������
	//	return (abs(a-c) + abs(c-b) < abs(a-b) + EPS);
	//}

	// �_a,b��ʂ钼���Ɠ_c�Ƃ̋���
	double distance_l_p(const P& a, const P& b, const P& c) {
		return abs(cross(b-a, c-a)) / abs(b-a);
	}

	// �_a,b��[�_�Ƃ�������Ɠ_c�Ƃ̋���
	double distance_ls_p(const P& a, const P& b, const P& c) {
		if ( dot(b-a, c-a) < EPS ) return abs(c-a);
		if ( dot(a-b, c-b) < EPS ) return abs(c-b);
		return abs(cross(b-a, c-a)) / abs(b-a);
	}

	// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�������
	bool is_intersected_ls(const P& a1, const P& a2, const P& b1, const P& b2) {
		return ( cross(a2-a1, b1-a1) * cross(a2-a1, b2-a1) < EPS ) &&
			( cross(b2-b1, a1-b1) * cross(b2-b1, a2-b1) < EPS );
	}

	// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�_�v�Z
	P intersection_ls(const P& a1, const P& a2, const P& b1, const P& b2) {
		P b = b2-b1;
		double d1 = abs(cross(b, a1-b1));
		double d2 = abs(cross(b, a2-b1));
		double t = d1 / (d1 + d2);

		return a1 + (a2-a1) * t;
	}

	// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�������
	bool is_intersected_l(const P& a1, const P& a2, const P& b1, const P& b2) {
		return !EQ( cross(a1-a2, b1-b2), 0.0 );
	}

	// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�_�v�Z
	P intersection_l(const P& a1, const P& a2, const P& b1, const P& b2) {
		P a = a2 - a1; P b = b2 - b1;
		return a1 + a * cross(b, b1-a1) / cross(b, a);
	}
}
