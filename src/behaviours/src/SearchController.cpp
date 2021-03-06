#include "SearchController.h"
#include <angles/angles.h>

SearchController::SearchController() {
  rng = new random_numbers::RandomNumberGenerator();
  currentLocation.x = 0;
  currentLocation.y = 0;
  currentLocation.theta = 0;

  centerLocation.x = 0;
  centerLocation.y = 0;
  centerLocation.theta = 0;
  result.PIDMode = FAST_PID;

  result.fingerAngle = M_PI/2;
  result.wristAngle = M_PI/4;
}

void SearchController::Reset() {
  result.reset = false;
}

/**
 * This code implements a basic random walk search.
 */
Result SearchController::DoWork() {

  if (!result.wpts.waypoints.empty()) {
    if (hypot(result.wpts.waypoints[0].x-currentLocation.x, result.wpts.waypoints[0].y-currentLocation.y) < 0.15) {
      attemptCount = 0;
    }
  }

  if (attemptCount > 0 && attemptCount < 5) {
    attemptCount++;
    if (succesfullPickup) {
      succesfullPickup = false;
      attemptCount = 1;
    }
    return result;
  }
  else if (attemptCount >= 5 || attemptCount == 0) 
  {
    attemptCount = 1;


    result.type = waypoint;
    Point  searchLocation;

    //select new position 50 cm from current location
    if (first_waypoint)
    {
      first_waypoint = false;

      //searchLocation.theta = tags[0].currentLocation.theta;
      //searchLocation.x = tags[0].currentLocation.x;
      //searchLocation.e-e-y = tags[0].currentLocation.y;
      
        /* searchLocation.theta = tags[1].getPositionZ();
	      searchLocation.x = tags[1].getPositionX();
	      searchLocation.y =tags[1].getPositionY();
		 
              result.wpts.waypoints.clear();
	      result.wpts.waypoints.insert(result.wpts.waypoints.begin(), searchLocation);
	      index++;

	      return result;*/
	 
      //searchLocation.theta = tags[20].getPositionZ();
      //searchLocation.x = tags[20].getPositionX();
      //searchLocation.y = tags[20].getPositionY();

      //searchLocation.theta = currentLocation.theta + M_PI;
      //searchLocatione-.x = currentLocation.x + (0.5 * cos(searchLocation.theta));
      //searchLocation.y = currentLocation.y + (0.5 * sin(searchLocation.theta));

      searchLocation.theta = 0.3;
      searchLocation.x = 0.1;
      searchLocation.y = 0.1;

    }
    else
    {

    
	     /* searchLocation.theta = tags[1].getPositionZ();
	      searchLocation.x = tags[1].getPositionX();
	      searchLocation.y =tags[1].getPositionY();
		 
              result.wpts.waypoints.clear();
	      result.wpts.waypoints.insert(result.wpts.waypoints.begin(), searchLocation);
	      index++;

	      return result;
	*/
	//select new heading from for(int i=index; i < tags.size(); i++)	
	// Gaussian distribution around current heading
      //searchLocation.theta = rng->gaussian(currentLocation.theta, 0.785398); //45 degrees in radians
      //searchLocation.x = currentLocation.x + (0.5 * cos(searchLocation.theta));
      //searchLocation.y = currentLocation.y + (0.5 * sin(searchLocation.theta));

      //searchLocation.theta = tags[0].currentLocation.theta;
      //searchLocation.x = tags[0].currentLocation.x;
      //searchLocation.y = tags[0].currentLocation.y;

      searchLocation.theta = 0.3;
      searchLocation.x = 0.2;
      searchLocation.y = 0.2;

    }

}
    result.wpts.waypoints.clear();
    result.wpts.waypoints.insert(result.wpts.waypoints.begin(), searchLocation);
    
    return result;

  

}

void SearchController::setTags(vector<Tag> argTags)
{

	cout<<"set tags"<<endl;
  

   tags.clear();

   for(int i=0; i < argTags.size(); i++)
   {
	tags.push_back(argTags[i]);
   }
      //for(int i=0; i < tags.size(); i++)
	//cout<<"tag :" << tags[i]<<endl;
	

}
void SearchController::SetCenterLocation(Point centerLocation) {
  
  float diffX = this->centerLocation.x - centerLocation.x;
  float diffY = this->centerLocation.y - centerLocation.y;
  this->centerLocation = centerLocation;
  
  if (!result.wpts.waypoints.empty())
  {
  result.wpts.waypoints.back().x -= diffX;
  result.wpts.waypoints.back().y -= diffY;
  }
  
}

void SearchController::SetCurrentLocation(Point currentLocation) {
  this->currentLocation = currentLocation;
}

void SearchController::ProcessData() {
}

bool SearchController::ShouldInterrupt(){
  ProcessData();

  return false;
}

bool SearchController::HasWork() {
  return true;
}

void SearchController::SetSuccesfullPickup() {
  succesfullPickup = true;
}


