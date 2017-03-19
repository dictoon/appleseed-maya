
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2017 Luis Barrancos, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "appleseedmaya/exporters/remapcolorexporter.h"

// Standard headers.
#include <algorithm>
#include <sstream>
#include <vector>

// Maya headers.
#include <maya/MFnDependencyNode.h>

// appleseed.renderer headers.
#include "renderer/api/utility.h"

// appleseed.maya headers.
#include "appleseedmaya/attributeutils.h"
#include "appleseedmaya/exporters/exporterfactory.h"
#include "appleseedmaya/shadingnodemetadata.h"

namespace asf = foundation;
namespace asr = renderer;

namespace
{

struct RemapColorEntry
{
    RemapColorEntry(float pos, float val, int in)
      : m_pos(pos)
      , m_value(val)
      , m_interp(in)
    {
    }

    bool operator<(const RemapColorEntry& other) const
    {
        return m_pos < other.m_pos;
    }

    float   m_pos;
    float   m_value;
    int     m_interp;
};

} // unnamed

void RemapColorExporter::registerExporter()
{
    NodeExporterFactory::registerShadingNodeExporter(
        "remapColor",
        &RemapColorExporter::create);
}

ShadingNodeExporter *RemapColorExporter::create(
    const MObject&      object,
    asr::ShaderGroup&   shaderGroup)
{
    return new RemapColorExporter(object, shaderGroup);
}

RemapColorExporter::RemapColorExporter(
    const MObject&      object,
    asr::ShaderGroup&   shaderGroup)
  : ShadingNodeExporter(object, shaderGroup)
{
}

void RemapColorExporter::exportParameterValue(
    const MPlug&        plug,
    const OSLParamInfo& paramInfo,
    asr::ParamArray&    shaderParams) const
{
    MFnDependencyNode depNodeFn(node());
    MStatus status;

    if (paramInfo.paramName == "in_red_Position")
    {
        MPlug plug = depNodeFn.findPlug("red", &status);

        std::vector<RemapColorEntry> remapColorValues;
        remapColorValues.reserve(plug.numElements());

        for(size_t i = 0, e = plug.numElements(); i < e; ++i)
        {
            MPlug entry = plug.elementByPhysicalIndex(i);
            MPlug position = entry.child(0);
            MPlug value = entry.child(1);
            MPlug interp = entry.child(2);

            float p;
            AttributeUtils::get(position, p);

            float v;
            AttributeUtils::get(value, v);

            int in;
            AttributeUtils::get(interp, in);

            remapColorValues.push_back(RemapColorEntry(p, v, in));
        }

        std::stringstream ssp;
        ssp << "float[] ";

        std::stringstream ssv;
        ssv << "float[] ";

        std::stringstream ssi;
        ssi << "int[] ";

        for(size_t i = 0, e = remapColorValues.size(); i < e; ++i)
        {
            ssp << remapColorValues[i].m_pos    << " ";
            ssv << remapColorValues[i].m_value  << " ";
            ssi << remapColorValues[i].m_interp << " ";
        }

        shaderParams.insert("in_red_Position"  , ssp.str().c_str());
        shaderParams.insert("in_red_FloatValue", ssv.str().c_str());
        shaderParams.insert("in_red_Interp"    , ssi.str().c_str());
    }
    else if (paramInfo.paramName == "in_green_Position")
    {
        MPlug plug = depNodeFn.findPlug("green", &status);

        std::vector<RemapColorEntry> remapColorValues;
        remapColorValues.reserve(plug.numElements());

        for(size_t i = 0, e = plug.numElements(); i < e; ++i)
        {
            MPlug entry = plug.elementByPhysicalIndex(i);
            MPlug position = entry.child(0);
            MPlug value = entry.child(1);
            MPlug interp = entry.child(2);

            float p;
            AttributeUtils::get(position, p);

            float v;
            AttributeUtils::get(value, v);

            int in;
            AttributeUtils::get(interp, in);

            remapColorValues.push_back(RemapColorEntry(p, v, in));
        }

        std::stringstream ssp;
        ssp << "float[] ";

        std::stringstream ssv;
        ssv << "float[] ";

        std::stringstream ssi;
        ssi << "int[] ";

        for(size_t i = 0, e = remapColorValues.size(); i < e; ++i)
        {
            ssp << remapColorValues[i].m_pos    << " ";
            ssv << remapColorValues[i].m_value  << " ";
            ssi << remapColorValues[i].m_interp << " ";
        }

        shaderParams.insert("in_green_Position"  , ssp.str().c_str());
        shaderParams.insert("in_green_FloatValue", ssv.str().c_str());
        shaderParams.insert("in_green_Interp"    , ssi.str().c_str());
    }
    else if (paramInfo.paramName == "in_blue_Position")
    {
        MPlug plug = depNodeFn.findPlug("blue", &status);

        std::vector<RemapColorEntry> remapColorValues;
        remapColorValues.reserve(plug.numElements());

        for(size_t i = 0, e = plug.numElements(); i < e; ++i)
        {
            MPlug entry = plug.elementByPhysicalIndex(i);
            MPlug position = entry.child(0);
            MPlug value = entry.child(1);
            MPlug interp = entry.child(2);

            float p;
            AttributeUtils::get(position, p);

            float v;
            AttributeUtils::get(value, v);

            int in;
            AttributeUtils::get(interp, in);

            remapColorValues.push_back(RemapColorEntry(p, v, in));
        }

        std::stringstream ssp;
        ssp << "float[] ";

        std::stringstream ssv;
        ssv << "float[] ";

        std::stringstream ssi;
        ssi << "int[] ";

        for(size_t i = 0, e = remapColorValues.size(); i < e; ++i)
        {
            ssp << remapColorValues[i].m_pos    << " ";
            ssv << remapColorValues[i].m_value  << " ";
            ssi << remapColorValues[i].m_interp << " ";
        }

        shaderParams.insert("in_blue_Position"  , ssp.str().c_str());
        shaderParams.insert("in_blue_FloatValue", ssv.str().c_str());
        shaderParams.insert("in_blue_Interp"    , ssi.str().c_str());
    }
    else if (paramInfo.paramName == "in_color")
    {
        // We save the colors at the same time we save the positions.
    }
    else
    {
        ShadingNodeExporter::exportParameterValue(
            plug,
            paramInfo,
            shaderParams);
    }
}

