//==========================================================================
///  @file      ScalableVectorGraphicsGenerator.cpp
///  @brief     Draw Graph
///  @version   1.0
///  @date      2017-12-26
//==========================================================================
#include "ScalableVectorGraphicsGenerator.hpp"
using std::endl;
ScalableVectorGraphicsGenerator::ScalableVectorGraphicsGenerator()
    : gateSize(50)
    , canvasWidth(1000)
    , canvasHeight(1000)
{
}

ScalableVectorGraphicsGenerator::~ScalableVectorGraphicsGenerator()
{
}

void ScalableVectorGraphicsGenerator::drawRectangle(int x, int y, int width, int height, std::string color)
{
    out << "\t<rect "
        << "x=\"" << x << "\" "
        << "y=\"" << y << "\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\" ";
    out << "fill=\""
        << color
        << "\" ";
    out << " />" << endl;
}

void ScalableVectorGraphicsGenerator::drawAND(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Z "
        << "\" fill=\"#FFBCD9\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawOR(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x << " " << y << " "
        << "\" fill=\"#8F5973\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawINV(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << "L "
        << x + gateSize + gateSize / 4 << " " << y + gateSize / 2 << " "
        << x << " " << y + gateSize << " "
        << "Z "
        << "\" fill=\"#008B8B\" />";
    out << endl;

    out << "\t<circle ";
    out << "cx=" << x + gateSize + gateSize / 4 << " "
        << "cy=" << y + gateSize / 2 << " "
        << "r=" << gateSize / 7 << " "
        << "fill=\"#008B8B\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawBuff(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << "L "
        << x + gateSize + gateSize / 4 << " " << y + gateSize / 2 << " "
        << x << " " << y + gateSize << " "
        << "Z "
        << "\" fill=\"#9370DB\" />";
    out << endl;//BDB76B
}

void ScalableVectorGraphicsGenerator::drawNAND(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Z "
        << "\" fill=\"#A2A2D0\" />";
    out << endl;

    out << "\t<circle ";
    out << "cx=" << x + gateSize + gateSize / 3 << " "
        << "cy=" << y + gateSize / 2 << " "
        << "r=" << gateSize / 7 << " "
        << "fill=\"#A2A2D0\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawNOR(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x << " " << y << " "
        << "\" fill=\"#FAD6A5\" />";
    out << endl;

    out << "\t<circle ";
    out << "cx=" << x + gateSize + gateSize / 3 << " "
        << "cy=" << y + gateSize / 2 << " "
        << "r=" << gateSize / 7 << " "
        << "fill=\"#FAD6A5\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawXNOR(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x + gateSize / 4 << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x + gateSize / 4 << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 + gateSize / 4 << " " << y + gateSize / 2 << " "
        << x + gateSize / 4 << " " << y << " "
        << "\" fill=\"#0247FE\" />";
    out << endl;

    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize / 8 << " " << y << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x + gateSize / 8 << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x << " " << y << " "
        << "\" fill=\"#0247FE\" />";
    out << endl;

    out << "\t<circle ";
    out << "cx=" << x + gateSize + gateSize / 3 << " "
        << "cy=" << y + gateSize / 2 << " "
        << "r=" << gateSize / 7 << " "
        << "fill=\"#0247FE\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawXOR(int x, int y)
{
    out << "\t<path d=";
    out << "\"M "
        << x + gateSize / 4 << " " << y << " "
        << x + gateSize << " " << y << " "
        << "Q "
        << x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
        << x + gateSize << " " << y + gateSize << " "
        << "L "
        << x + gateSize / 4 << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 + gateSize / 4 << " " << y + gateSize / 2 << " "
        << x + gateSize / 4 << " " << y << " "
        << "\" fill=\"#00C4B0\" />";
    out << endl;

    out << "\t<path d=";
    out << "\"M "
        << x << " " << y << " "
        << x + gateSize / 8 << " " << y << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x + gateSize / 8 << " " << y + gateSize << " "
        << "L "
        << x << " " << y + gateSize << " "
        << "Q "
        << x + gateSize / 2 << " " << y + gateSize / 2 << " "
        << x << " " << y << " "
        << "\" fill=\"#00C4B0\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawIOBox(int x, int y, int flag)
{
    if (flag == 0) {
        drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "#FBEC5D");
    }
    else if ( flag == 1 ){
        drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "#FD7C6E");
    } else {
        drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "#A9A9A9");
    }
}

int rid=0;
void ScalableVectorGraphicsGenerator::drawPath(std::vector< int >& path)
{
	// Dark turquoise ( light blue ),Columbia Blue, Cadmium red, Cosmic Cobalt, Dark pastel green, dark slate gray, dodger blue
	std::string name[7] = {"#00CED1", "#C4D8E2", "#E30022", "#2E2D88", "#03C03C", "#2F4F4F", "#0000FF"};
	srand(time(NULL));
	int index = rid % 7;	
	rid++;
    out << "\t<path d=";
    out << "\"M " << path[0] << " " << path[1] << " ";
    out << "L ";
    for (int i = 2; i < path.size(); ++i)
        out << path[i] << " ";
	out << "\" stroke=\"" << name[index] << "\"" << " "
	    << "stroke-width=\"2\" />";
    out << endl;
}

void ScalableVectorGraphicsGenerator::drawText(int x, int y, int text)
{
    out << "\t<text "
        << "x=\"" << x + gateSize / 2 << "\" "
        << "y=\"" << y + gateSize / 2 << "\" style=\"font-size:23px;\" >"
        << text << "</text>";
    out << endl;
}

void ScalableVectorGraphicsGenerator::SVGBegin(std::string filename, int width, int height)
{
    out.open(std::string(filename+".html").c_str(), std::ios::out);
    out << "<svg "
        << "width=\"" << width << "px\" "
        << "height=\"" << height << "px\">" << endl;
    canvasWidth = width;
    canvasHeight = height;
}

void ScalableVectorGraphicsGenerator::SVGEnd()
{
    out << "</svg>" << endl;
    out.close();
}

void ScalableVectorGraphicsGenerator::setGateSize(int inSize)
{
    gateSize = inSize;
}

int ScalableVectorGraphicsGenerator::getGateSize()
{
    return gateSize;
}
