
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2016 Haggi Krey, The appleseedhq Organization
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

#ifndef APPLESEED_MAYA_SESSION_H
#define APPLESEED_MAYA_SESSION_H

// boost headers.
#include "boost/filesystem/path.hpp"

// Maya headers.
#include <maya/MStatus.h>
#include <maya/MString.h>

// appleseed.foundation headers.
#include "foundation/utility/autoreleaseptr.h"

// appleseed.renderer headers.
#include "renderer/api/rendering.h"

// appleseed.maya headers.
#include "appleseedmaya/renderercontroller.h"

// Forward declarations.
namespace renderer { class Project; }


class AppleseedSession
{
  public:

    static MStatus initialize(const MString& pluginPath);
    static MStatus uninitialize();

    struct Options
    {
        Options()
          : m_width(-1)
          , m_height(-1)
          , m_ipr(false)
          , m_selectionOnly(false)
          , m_sequence(false)
          , m_firstFrame(0)
          , m_lastFrame(0)
        {
        }

        // Common options.
        int m_width;
        int m_height;
        MString m_camera;

        // Final render options.

        // IPR options.
        bool m_ipr;

        // Export options.
        bool m_selectionOnly;
        bool m_sequence;
        int m_firstFrame;
        int m_lastFrame;
    };

    static void beginProjectExport(
        const MString& fileName,
        const Options& options);

    static void endProjectExport();

    static void beginFinalRender(
        const Options& options);

    static void endFinalRender();

    static void beginProgressiveRender(
        const Options& options);

    static void endProgressiveRender();

    // Destructor.
    ~AppleseedSession();

  private:

    // Constructor. (IPR or Batch)
    AppleseedSession();

    // Constructor. (Scene export)
    explicit AppleseedSession(const MString& fileName);

    // Non-copyable
    AppleseedSession(const AppleseedSession&);
    AppleseedSession& operator=(const AppleseedSession&);

    void createProject();

    void exportScene(const Options& options);

    void exportRenderGlobals(const Options& options);

    bool writeProject() const;
    bool writeProject(const char* fileName) const;

    foundation::auto_release_ptr<renderer::Project> m_project;

    MString m_fileName;
    boost::filesystem::path m_projectPath;

    renderer::MasterRenderer *m_renderer;
    RendererController m_rendererController;
};

#endif  // !APPLESEED_MAYA_SESSION_H
