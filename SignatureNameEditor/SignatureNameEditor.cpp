// SignatureNameEditor.cpp : ���C�� �v���W�F�N�g �t�@�C���ł��B

#include "stdafx.h"
//#include "SignPreview.h"
#include "Scan.h"

using namespace SignatureNameEditor;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �R���g���[�����쐬�����O�ɁAWindows XP �r�W���A�����ʂ�L���ɂ��܂�
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ���C�� �E�B���h�E���쐬���āA���s���܂�
	//Application::Run(gcnew SignPreview());
	Application::Run(gcnew Scan());
	return 0;
}
