using UnityEngine;
using System.Collections;

namespace JJBJ.J1.Action
{
	public class MoveCurve
	{
		public event System.Action OnBegin;
		public event System.Action OnEnd;
		
		public bool isContinued 
		{
			get;
			private set;
		}
		
		public void Begin (MonoBehaviour target, CharacterController controller, Vector2 moveTo, Vector2 moveFinish, float totalRetainTick) 
		{
			if (this.isContinued == false)
			{
				this.isContinued = true;
				
				target.StartCoroutine
				(
					Continue
					(
						target,
						controller,
						moveTo,
						moveFinish,
						totalRetainTick
					)
				);
			}
		}

		private IEnumerator Continue (MonoBehaviour target, CharacterController controller, Vector2 moveTo, Vector2 moveFinish, float totalRetainTick)
		{
			RaiseEvent (OnBegin);

			Vector3 moveFrom = target.transform.position;
			Vector3 moveDistance = new Vector3(moveTo.x - moveFrom.x, moveTo.y - moveFrom.y, 0.0f);

			float beginTick = Time.time;
			float retainTick = totalRetainTick / 2;

			while (this.isContinued == true)
			{
				float deltaRetainTick = Time.time - beginTick;
				
				if (deltaRetainTick > retainTick)
				{
					break;
				}
				else
				{
					float ratioX = deltaRetainTick / retainTick;
					float ratioY = (2.0f - ratioX) * ratioX;

					target.transform.position = new Vector3
					(
						moveFrom.x + moveDistance.x * ratioX,
						moveFrom.y + moveDistance.y * ratioY,
						moveFrom.z
					);
				}
				
				yield return null;
			}

			moveFrom = moveTo;
			moveDistance = new Vector3(moveFinish.x - moveFrom.x, moveFinish.y - moveFrom.y, 0.0f);

			beginTick = Time.time; 

			while (this.isContinued == true)
			{
				float deltaRetainTick = Time.time - beginTick; 

				if (deltaRetainTick > retainTick)
				{
					End (target);
				}
				else
				{
					float ratioX = deltaRetainTick / retainTick;
					float ratioY = ratioX * ratioX;

					target.transform.position = new Vector3
					(
						moveFrom.x + moveDistance.x * ratioX,
						moveFrom.y + moveDistance.y * ratioY,
						moveFrom.z
					);
				}
				
				yield return null;
			}
		}

		private void End (MonoBehaviour target)
		{
			this.isContinued = false;
			RaiseEvent (OnEnd);
		}

		private void RaiseEvent (System.Action raiseEvent)
		{
			if (raiseEvent != null) 
			{
				raiseEvent ();
			}
		}
	}
}