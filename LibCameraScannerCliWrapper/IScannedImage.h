#pragma once
namespace CameraScanner { namespace CLI {
	using namespace System;
	using namespace System::Xml::Serialization;
	using namespace System::Drawing;

	// 命名規則 関数は大文字から始める

	public interface class IScannedImage
	{
	public:
		Void SaveImage();
		Void SaveImage(String^ file_name);
		virtual String^ ToString();

		[XmlIgnore]
		property Image^ Page
		{
			Image^ get();
			Void set(Image^ value);
		}
		property String^ FileName
		{
			String^ get();
			Void set(String^ value);
		}
		property String^ ImagePath
		{
			String^ get();
			Void set(String^ valaue);
		}
		property DateTime TimeTaken
		{
			DateTime get();
			Void set(DateTime value);
		}
		property Boolean NeedToBeSaved
		{
			Boolean get();
		}
	};
}}
