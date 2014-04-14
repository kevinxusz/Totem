#include "color2gray.h"
#include "designnet/designnet_core/data/imagedata.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "Utils/varianthelper.h"
using namespace DesignNet;
namespace Conversion{
#define DATA_LABEL_COLORIMAGE	"ColorImage"
#define DATA_LABEL_GRAYIMAGE	"GrayImage"


Color2Gray::Color2Gray(DesignNet::DesignNetSpace *space, QObject *parent)
	: Processor(space, parent)
{
	setName(tr("Color 2 Gray"));
	addPort(Port::IN_PORT, DATATYPE_8UC3IMAGE, DATA_LABEL_COLORIMAGE);
	addPort(Port::OUT_PORT, DATATYPE_GRAYIMAGE, DATA_LABEL_GRAYIMAGE);
}

Color2Gray::~Color2Gray()
{

}

QString Color2Gray::title() const
{
	return tr("Color 2 Gray");
}

QString Color2Gray::category() const
{
	return tr("Conversion");
}

bool Color2Gray::process(QFutureInterface<ProcessResult> &future)
{
	notifyDataWillChange();
	Port* port = getPort(Port::IN_PORT, DATA_LABEL_COLORIMAGE);
	cv::Mat mat = getData(DATA_LABEL_COLORIMAGE).at(0)->variant.value<cv::Mat>();
	if (!mat.empty())
	{
		cv::cvtColor(mat, mat, CV_BGR2GRAY);
		pushData(qVariantFromValue(mat), DATATYPE_GRAYIMAGE, DATA_LABEL_GRAYIMAGE);
		notifyProcess();
		emit logout("Color2Gray::process() OK");
		return true;
	}
 	return false;
}

void Color2Gray::propertyChanged( Property *prop )
{

}

}