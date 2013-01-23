#pragma once
#include <complex>
namespace Line
{
	typedef std::complex<double> P;

	// ���e����덷��
#define EPS (1e-10)
	// 2�̃X�J���[�����������ǂ���
#define EQ(a,b) (abs((a)-(b)) < EPS)
	// 2�̃x�N�g�������������ǂ���
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

	// �x�N�g��a�̐�Βl�����߂�
	double length(const P& a);

	// 2�_a,b�Ԃ̋��������߂�
	double distance(const P& a, const P& b);

	// �x�N�g��a�̒P�ʃx�N�g�������߂�
	P unit_vector(const P& a);

	// �x�N�g��a�̖@���x�N�g��n1,n2�����߂�
	std::pair<P, P> normal(const P& a);

	// �x�N�g��a�̒P�ʖ@���x�N�g��un1,un2�����߂�
	std::pair<P, P> unit_normal(const P& a);

	// ���� (dot product) : a�Eb = |a||b|cos��
	double dot(const P& a, const P& b);

	// �O�� (cross product) : a�~b = |a||b|sin��
	double cross(const P& a, const P& b);

	// 2�����̒��𔻒� : a��b <=> dot(a, b) = 0
	bool is_orthogonal(const P& a1, const P& a2, const P& b1, const P& b2);

	// 2�����̕��s���� : a//b <=> cross(a, b) = 0
	bool is_parallel(const P& a1, const P& a2, const P& b1, const P& b2);

	// �_c������a,b��ɂ��邩�Ȃ���
	bool is_point_on_line(const P& a, const P& b, const P& c);

	// �_a,b��ʂ钼���Ɠ_c�Ƃ̋���
	double distance_l_p(const P& a, const P& b, const P& c);

	// �_a,b��[�_�Ƃ�������Ɠ_c�Ƃ̋���
	double distance_ls_p(const P& a, const P& b, const P& c);

	// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�������
	bool is_intersected_ls(const P& a1, const P& a2, const P& b1, const P& b2);

	// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�_�v�Z
	P intersection_ls(const P& a1, const P& a2, const P& b1, const P& b2);

	// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�������
	bool is_intersected_l(const P& a1, const P& a2, const P& b1, const P& b2);

	// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�_�v�Z
	P intersection_l(const P& a1, const P& a2, const P& b1, const P& b2);
}
