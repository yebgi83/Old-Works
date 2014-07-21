using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
[RequireComponent(typeof(SpriteRenderer))]
public class SpriteAnimationRenderer : MonoBehaviour 
{
	#region Components 
	struct Components
	{
		public SpriteRenderer spriteRenderer;
	}
	
	private Components components;
	#endregion

	#region Variables
	public int frameRate;
	public SpriteAnimation spriteAnimation;

	public bool isLooping
	{
		get;
		private set;
	}
	
	public bool isPlaying
	{
		get;
		private set;
	}

	private int? frameIndex;
	private float? beginTick;
	#endregion

	void Awake ()
	{
		this.components = new Components()
		{
			spriteRenderer = GetComponent<SpriteRenderer>()
		};
	}

	// Update is called once per frame
	void Update () 
	{
		if (this.isPlaying == true)
		{
			float retainTick = 1.0f / this.frameRate;

			if (Time.time - this.beginTick.Value >= retainTick)
			{
				this.beginTick += retainTick;
				this.frameIndex++;

				if (RenderFrame (this.frameIndex.Value) == false)
				{
					if (this.isLooping == true)
					{
						RenderFrame (0);
						this.frameIndex = 0;
					}
					else
					{
						StopPlay ();
					}
				}
			}
		}
		else
		{
			RenderFrame (0);
		}
	}

	public void Play (SpriteAnimation spriteAnimation, bool isLooping)
	{
		this.spriteAnimation = spriteAnimation;
		this.isLooping = isLooping;
		this.isPlaying = true;
		this.frameIndex = 0;
		this.beginTick = Time.time;
	}

	public void StopPlay ()
	{
		this.isLooping = false;
		this.isPlaying = false;
		this.frameIndex = null;
		this.beginTick = null;
	}

	private bool RenderFrame (int frameIndex)
	{
		if (this.spriteAnimation == null)
		{
			return false;
		}

		if (this.components.spriteRenderer == null)
		{
			return false;
		}
		else
		{
			return this.spriteAnimation.Render (this.components.spriteRenderer, frameIndex);
		}
	}
}
