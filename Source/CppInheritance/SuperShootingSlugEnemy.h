/*********************************************************************
* Module 1. Programming Foundations
* Author: David Vallejo Fern�ndez    David.Vallejo@uclm.es
*         Santiago S�nchez Sobrino   Santiago.Sanchez@uclm.es
*
* You can redistribute and/or modify this file under the terms of the
* GNU General Public License ad published by the Free Software
* Foundation, either version 3 of the License, or (at your option)
* and later version. See <http://www.gnu.org/licenses/>.
*
* This file is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "SuperShootingSlugEnemy.generated.h"


UCLASS()
class CPPINHERITANCE_API ASuperShootingSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuperShootingSlugEnemy();
	static const FString TYPE_KEY;

private:
	void RunBehaviour() override;
};
