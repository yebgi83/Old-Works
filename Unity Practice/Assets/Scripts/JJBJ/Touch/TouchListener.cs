using UnityEngine;

using System;
using System.Collections;

namespace JJBJ.TouchListener
{
	public class TouchListener 
	{
		public event System.Action<Vector2> OnBegin;
		public event System.Action<Vector2> OnContinue;
		public event System.Action<Vector2> OnEnd;

		private bool isContinued;

		public void Begin (MonoBehaviour target)
		{
			if (this.isContinued == false)
			{
				this.isContinued = true;
				target.StartCoroutine (Continue(target));
			}
		}
		
		private IEnumerator Continue (MonoBehaviour target)
		{
			while (this.isContinued == true)
			{
				if (Application.isPlaying == false)
				{
					End (target);
				}
				else
				{
					switch (Application.platform)
					{
						case RuntimePlatform.Android:
						case RuntimePlatform.IPhonePlayer:
						{
							TouchListenerOnMobile.Listen (this, target);
						}
						break;
					
						default:
						{
							if (Application.isEditor == true) 
							{
								TouchListenerOnEditor.Listen (this, target);	
							}
							else 
							{
								throw new InvalidOperationException ("Simulation mode can run in editor mode.");
							}
						}
						break;
					}
				}
				
				yield return null;
			}
		}
		
		public void End (MonoBehaviour target)
		{
			this.isContinued = false;
		}

		internal void RaiseOnBegin (Vector2 position)
		{
			if (OnBegin != null) 
			{
				OnBegin (position);
			}
		}

		internal void RaiseOnContinue (Vector2 position)
		{
			if (OnContinue != null) 
			{
				OnContinue (position);
			}
		}

		internal void RaiseOnEnd (Vector2 position)
		{
			if (OnEnd != null) 
			{
				OnEnd (position);
			}
		}
	}

	static internal class TouchListenerOnMobile
	{
		static internal void Listen (TouchListener listener, MonoBehaviour target)
		{
			foreach (Touch touch in Input.touches)
			{
				switch (touch.phase) 
				{
					case TouchPhase.Began:
					{
						listener.RaiseOnBegin (touch.position);
					}
					break;
				
					case TouchPhase.Ended:
					{
						listener.RaiseOnEnd (touch.position);
					}
					break;

					case TouchPhase.Moved:
					case TouchPhase.Canceled:
					case TouchPhase.Stationary:
					{
						listener.RaiseOnContinue (touch.position);
					}
					break;
				}
			}
		}
	}

	static internal class TouchListenerOnEditor
	{
		static private Vector2? oldMousePosition;

		static internal void Listen (TouchListener listener, MonoBehaviour target)
		{
			Vector2 mousePosition = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
			
			if (Input.GetMouseButtonDown(0) == true) 
			{
				listener.RaiseOnBegin (mousePosition);
			}

			if (Input.GetMouseButtonUp(0) == true) 
			{
				listener.RaiseOnEnd (mousePosition);
			} 

			if (Input.GetMouseButton(0) == true) 
			{
				if (TouchListenerOnEditor.oldMousePosition.HasValue == true) 
				{
					Vector2 deltaMousePosition = mousePosition - TouchListenerOnEditor.oldMousePosition.Value;
					
					if (deltaMousePosition.magnitude != 0.0f) 
					{
						listener.RaiseOnContinue (mousePosition);
					}
				}
			}

			TouchListenerOnEditor.oldMousePosition = mousePosition;
		}
	}
}