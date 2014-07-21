using UnityEngine;
using System;

[Serializable]
public class SpriteAnimation : ScriptableObject 
{
	public int 	    numberOfFrames;
	public Material spriteSheet;

	public bool Render (SpriteRenderer spriteRenderer, int frameIndex)
	{
		if (this.numberOfFrames <= 0)
		{
			return false;
		}

		if (this.spriteSheet == null)
		{
			return false;
		}

		Renderer renderer = spriteRenderer.renderer;

		if (renderer.sharedMaterial != this.spriteSheet)
		{
			renderer.sharedMaterial = this.spriteSheet;
		}

		float offsetX = renderer.sharedMaterial.mainTextureScale.x * frameIndex;

		if (offsetX < 0.0f || offsetX >= 1.0f)
		{
			return false;
		}
		else
		{
			renderer.sharedMaterial.mainTextureOffset = new Vector2 (offsetX, 0.0f);
			renderer.sharedMaterial.mainTextureScale = new Vector2 (1.0f / this.numberOfFrames, 1.0f);
			return true;
		}
	}
}
