#pragma once

#include <memory>
#include <vector>
#include <array>
#include <ospcommon/vec.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

#include "Imgui3dExport.h"
#include <ospray/ospray_cpp/TransferFunction.h>
#include "common/sg/transferFunction/TransferFunction.h"

namespace ospray {

  class OSPRAY_IMGUI3D_INTERFACE TransferFunction
  {
    // A line is made up of points sorted by x, its coordinates are
    // on the range [0, 1]
    struct Line
    {
      std::vector<ospcommon::vec2f> line;
      int color;

      // TODO: Constructor that takes an existing line
      // Construct a new diagonal line: [(0, 0), (1, 1)]
      Line();
      /* Move a point on the line from start to end, if the line is
       * not split at 'start' it will be split then moved
       * TODO: Should we have some cap on the number of points? We should
       * also track if you're actively dragging a point so we don't recreate
       * points if you move the mouse too fast
       */
      void movePoint(const float &startX, const ospcommon::vec2f &end);
      // Remove a point from the line, merging the two segments on either side
      void removePoint(const float &x);
    };
    // The transfer function color presets available
    enum ColorMap {
      JET,
      ICE_FIRE,
      COOL_WARM,
      BLUE_RED,
      GRAYSCALE,
      CUSTOM
    };

    // The scenegraph transfer function being manipulated by this widget
    std::shared_ptr<sg::TransferFunction> transferFcn;
    // Lines for RGBA transfer function controls
    std::array<Line, 4> rgbaLines;
    // The line currently being edited
    int activeLine;
    // The selected transfer function being shown
    int tfcnSelection;

    // Track if the function changed and must be re-uploaded.
    // We start by marking it changed to upload the initial palette
    bool fcnChanged;

    /* The 2d palette texture on the GPU for displaying the color map in the UI.
     */
    GLuint paletteTex;

  public:
    TransferFunction(std::shared_ptr<sg::TransferFunction> &tfn);
    ~TransferFunction();
    TransferFunction(const TransferFunction &t);
    TransferFunction& operator=(const TransferFunction &t);
    /* Draw the transfer function editor widget
    */
    void drawUi();
    /* Render the transfer function to a 1D texture that can
     * be applied to volume data
     */
    void render();

  private:
    // Select the provided color map specified by tfcnSelection
    void setColorMap();
    // TODO: Save/load the transfer function through the file dialog
    //void save_fcn() const;
    //void load_fcn();
  };

}// ::ospray
