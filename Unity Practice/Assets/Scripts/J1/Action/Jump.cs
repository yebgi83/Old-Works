using UnityEngine;

using System;
using System.Collections;

namespace JJBJ.J1.Action
{
	public class Jump
	{
		public event System.Action OnBegin;
		public event System.Action OnContinue;
		public event System.Action OnEnd;

		private Vector3? velocity;
		private Vector3? gravityAccelation;
		
		public bool isContinued
		{
			get;
			private set;
		}
		
		public int jumpCount
		{
			get;
			private set;
		}
		
		public void Begin
		(
			MonoBehaviour target,
			CharacterController characterController,
			Vector2 initVelocity, 
			Vector2 gravityAccelation
		) 
		{
			if (this.isContinued == false)
			{
				this.isContinued = true;

				target.StartCoroutine
				(
					Continue
					(
						target,
						characterController,
						initVelocity,
						gravityAccelation
					)
				);
			}
			else
			{
				this.velocity += new Vector3(initVelocity.x, initVelocity.y, 0.0f);
				this.gravityAccelation = new Vector3(gravityAccelation.x, gravityAccelation.y, 0.0f);
				this.jumpCount++;
				
				RaiseEvent (OnContinue);
			}
		}

		private IEnumerator Continue
		(
			MonoBehaviour target, 
			CharacterController characterController,
			Vector2 initVelocity,
			Vector2 gravityAccelation
		)
		{
			RaiseEvent (OnBegin);

			this.velocity = new Vector3(initVelocity.x, initVelocity.y, 0.0f);
			this.gravityAccelation = new Vector3(gravityAccelation.x, gravityAccelation.y, 0.0f);
			this.jumpCount = 1;
			
			while (this.isContinued == true)
			{
				if (this.gravityAccelation.Value.y == 0.0f) 
				{
					throw new InvalidOperationException("GravityAcceltation.y must be not zero.");
				}

				if (characterController.isGrounded == true)
				{
					End (target);
				}

				target.transform.position += this.velocity.Value;
				this.velocity += this.gravityAccelation.Value;

				yield return null;
			} 
		}
		
		private void End (MonoBehaviour target)
		{
			this.velocity = null;
			this.gravityAccelation = null;
			this.jumpCount = 0;
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