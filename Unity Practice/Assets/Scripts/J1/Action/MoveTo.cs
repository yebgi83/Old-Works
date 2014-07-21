using UnityEngine;
using System.Collections;

namespace JJBJ.J1.Action
{
	public class MoveTo
	{
		public event System.Action OnBegin;
		public event System.Action OnEnd;
		
		public bool isContinued 
		{
			get;
			private set;
		}
		
		public void Begin (MonoBehaviour target, Vector2 moveFinish, float totalRetainTick) 
		{
			if (this.isContinued == false)
			{
				this.isContinued = true;
				
				target.StartCoroutine
				(
					Continue
					(
						target,
						moveFinish,
						totalRetainTick
					)
				);
			}
		}
		
		private IEnumerator Continue (MonoBehaviour target, Vector2 moveFinish, float totalRetainTick)
		{
			RaiseEvent (OnBegin);
			
			Vector3 moveFrom = target.transform.position;
			Vector3 moveDistance = new Vector3(moveFinish.x - moveFrom.x, moveFinish.y - moveFrom.y, 0.0f);
			
			float beginTick = Time.time;
			float retainTick = totalRetainTick;
			
			while (this.isContinued == true)
			{
				float deltaRetainTick = Time.time - beginTick;
				
				if (deltaRetainTick > retainTick)
				{
					End (target);
				}
				else
				{
					float ratio = deltaRetainTick / retainTick;

					target.transform.position = new Vector3
					(
						moveFrom.x + moveDistance.x * ratio,
						moveFrom.y + moveDistance.y * ratio,
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