#pragma once
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>

namespace Signature
{
	template<typename ArrayIn, typename ArrayOut>
	ArrayOut convertArray(const ArrayIn& src)
	{
		ArrayOut out;
		for (ArrayIn::const_iterator it=src.begin(); it!=src.end(); it++)
			out.push_back(*it);
		return out;
	}

	namespace Image
	{
		static const std::string default_type = "SURF";
		typedef int ID;
		struct Base
		{
			ID id;
			cv::Mat signature;
			Base();
			Base(ID id, const cv::Mat& signature);
			Base(const Base& src);
			Base(const Base* src);
			Base& operator=(const Base& src);
			virtual ~Base();
			virtual std::string getName() const = 0;
		};
		struct Conclusive : public Base
		{
			std::string name;
			Conclusive();
			Conclusive(ID id, const cv::Mat& signature, const std::string& name);
			Conclusive(const Base& src);
			Conclusive(const Conclusive& src);
			Conclusive& operator=(const Conclusive& src);
			virtual ~Conclusive();
			virtual std::string getName() const;
		};
		struct Candidate : public Base
		{
			struct Assessment
			{
				std::string name;
				double score;
				Assessment();
				bool operator<(const Assessment& val) const;
			};
			std::list<Assessment> names;
			Candidate();
			Candidate(ID id, const cv::Mat& signature);
			Candidate(ID id, const cv::Mat& signature, std::list<Assessment> names);
			Candidate(const Candidate& src);
			Candidate& operator=(const Candidate& src);
			operator Conclusive() const;
			virtual ~Candidate();
			virtual std::string getName() const;
		};
		class MatchingMachines
		{
		protected:
			std::string type;
			cv::Ptr<cv::FeatureDetector> detector;
			cv::Ptr<cv::DescriptorExtractor> extractor;

		public:
			MatchingMachines();
			MatchingMachines(const std::string& type);
			MatchingMachines(const cv::Ptr<cv::FeatureDetector>& detector, const cv::Ptr<cv::DescriptorExtractor>& extractor, const std::string& type);
			MatchingMachines(const MatchingMachines& src);
			MatchingMachines& operator=(const MatchingMachines& src);
			virtual ~MatchingMachines();

		public:
			cv::Ptr<cv::FeatureDetector> getDetector() const;
			cv::Ptr<cv::DescriptorExtractor> getExtractor() const;
			std::string getName() const;

		protected:
			void make();
		};
		class Info
		{
		protected:
			typedef std::vector<cv::KeyPoint> KeyPoints;
			typedef cv::Mat Descriptor;
			typedef int Idx;
			std::vector<ID> ids;
			std::vector<cv::Mat> images;
			std::vector<KeyPoints> keypoints;
			std::vector<Descriptor> descriptors;
			std::vector<std::string> names;
		public:
			Info();
			Info(const Info& src);
			Info& operator=(const Info& src);
			virtual ~Info();

			void prepare(const std::list<std::shared_ptr<Base> >& signatures, const MatchingMachines& machines);
			virtual void addSignature(const Base& signature, const MatchingMachines& machines);

			ID getID(Idx idx) const;
			cv::Mat getImage(Idx idx) const;
			KeyPoints getKeyPoints(Idx idx) const;
			Descriptor getDescriptor(Idx idx) const;
			std::vector<Descriptor> getDescriptors() const;
			std::string getName(Idx idx) const;

			size_t size() const;
			virtual void clear();
			virtual void resize(size_t size);
		protected:
			void setID(Idx idx, ID id);
			void setImage(Idx idx, const cv::Mat& image, bool make_clone = false);
			void setKeyPoints(Idx idx, const KeyPoints& keypoints);
			void setDescriptor(Idx idx, const Descriptor& descriptor);
			void setName(Idx idx, const std::string& name);

			void addSignature(const Base& signature, int idx);
		};
	}
	namespace Guess
	{
		typedef std::list<Image::Candidate::Assessment> Result;
		class Base
		{
		protected:
			Image::Info info;
			Image::MatchingMachines machines;
		public:
			Base();
			Base(const Base& src);
			Base& operator=(const Base& src);
			virtual ~Base();

			const Image::Info& getInfo() const;
			void setMatchingMachine(const std::string& type);
			void setMatchingMachine(const Image::MatchingMachines& machines);
			virtual void buildInfo(const std::list<std::shared_ptr<Image::Base> >& images);
			virtual Result match(const Image::Info& query, int idx) = 0;
		};
	}
}
