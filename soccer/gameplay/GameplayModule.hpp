// kate: indent-mode cstyle; indent-width 4; tab-width 4; space-indent false;
// vim:ai ts=4 et

#pragma once

#include <QMutex>
#include <set>

#include <framework/Module.hpp>

#include "ui_PlayConfigTab.h"

#include "Robot.hpp"

namespace Gameplay
{
	class Behavior;
	class Play;
	
	class GameplayModule: public QObject, public Module
	{
		Q_OBJECT;
		public:
			typedef boost::shared_ptr<GameplayModule> shared_ptr;
			GameplayModule(SystemState *state);
			~GameplayModule();
			
			SystemState *state() const
			{
				return _state;
			}
			
			void createGoalie();
			void removeGoalie();
			
			Behavior *goalie() const
			{
				return _goalie;
			}
			
			Play *currentPlay() const
			{
				return _currentPlay;
			}
			
			virtual void fieldOverlay(QPainter&, Packet::LogFrame&) const;
			virtual void run();
			
			Gameplay::Play *selectPlay();
			
			////////
			// Useful matrices:
			// Each of these converts coordinates in some other system to team space.
			// Use them in a play or behavior like this:
			//   team = _gameplay->oppMatrix() * Geometry2d::Point(1, 0);
			
			// Centered on the ball
			Geometry2d::TransformMatrix ballMatrix() const
			{
				return _ballMatrix;
			}
			
			// Center of the field
			Geometry2d::TransformMatrix centerMatrix() const
			{
				return _centerMatrix;
			}
			
			// Opponent's coordinates
			Geometry2d::TransformMatrix oppMatrix() const
			{
				return _oppMatrix;
			}
			
			Robot *self[Constants::Robots_Per_Team];
			Robot *opp[Constants::Robots_Per_Team];
			
		protected:
			friend class Play;
			
			SystemState *_state;
			
			// The goalie behavior (may be null)
			Behavior *_goalie;
			
			// The current play
			Play *_currentPlay;
			
			// True if the current play is finished and a new one should be selected during the next frame
			bool _playDone;
			
			Geometry2d::TransformMatrix _ballMatrix;
			Geometry2d::TransformMatrix _centerMatrix;
			Geometry2d::TransformMatrix _oppMatrix;
			
			ObstaclePtr _sideObstacle;
			
			//outside of the floor boundaries
			ObstaclePtr _nonFloor[4];
			
			//goal area
			ObstaclePtr _goalArea[3];
			
			// sets of plays with names as lookups
			std::map<std::string, Play *> _plays;
			std::map<std::string, Play *> _AvailablePlays;

			// GUI Components
		protected Q_SLOTS:
			void removeAllPlays();
			void addAllPlays();
			void addPlay(QListWidgetItem*index);
			void removePlay(QListWidgetItem* index);
			void updateCurrentPlay(QString playname);
			void loadPlaybook();
			void savePlaybook();
			void useGoalie(int state);

		protected:
		    Ui_PlayConfig ui;
	};
}
