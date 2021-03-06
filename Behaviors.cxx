/******************************************************************************

  This source file is part of the TEM tomography project.

  Copyright Kitware, Inc.

  This source code is released under the New BSD License, (the "License").

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

******************************************************************************/
#include "Behaviors.h"

#include "pqAlwaysConnectedBehavior.h"
#include "pqApplicationCore.h"
#include "pqDefaultViewBehavior.h"
#include "pqInterfaceTracker.h"
#include "pqPersistentMainWindowStateBehavior.h"
#include "pqQtMessageHandlerBehavior.h"
#include "pqStandardPropertyWidgetInterface.h"
#include "pqStandardViewModules.h"
#include "pqViewFrameActionsBehavior.h"

namespace TEM
{
//-----------------------------------------------------------------------------
Behaviors::Behaviors(QMainWindow* mainWindow)
{
  Q_ASSERT(mainWindow);

  // Register ParaView interfaces.
  pqInterfaceTracker* pgm = pqApplicationCore::instance()->interfaceTracker();

  // * adds support for standard paraview views.
  pgm->addInterface(new pqStandardViewModules(pgm));

  // * add support for ParaView properties panel widgets.
  pgm->addInterface(new pqStandardPropertyWidgetInterface(pgm));

  // Load plugins distributed with application.
  pqApplicationCore::instance()->loadDistributedPlugins();

  new pqQtMessageHandlerBehavior(this);
  new pqViewFrameActionsBehavior(this);
  new pqDefaultViewBehavior(this);
  new pqAlwaysConnectedBehavior(this);
  new pqPersistentMainWindowStateBehavior(mainWindow);

  // this will trigger the logic to setup reader/writer factories, etc.
  pqApplicationCore::instance()->loadConfigurationXML("<xml/>");
}

//-----------------------------------------------------------------------------
Behaviors::~Behaviors()
{
}

} // end of namespace TEM
