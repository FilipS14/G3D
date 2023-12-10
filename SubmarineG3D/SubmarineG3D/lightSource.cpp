const float colorChangePeriod = 5.0f;
const float colorChangePeriod1 = 0.015f;
float lastColorChangeTime = 0.0f;
float lastColorChangeTime1 = 0.0f;
float Fincrement = 0.0075f;
int ok = 0;
std::string day_night = "day";

if (currentFrame - lastColorChangeTime1 >= colorChangePeriod1) {
	if (lightPos.x >= 3.0f)
	{
		//ok = 1;
		if (day_night == "day")
		{
			day_night = "night";
		}
		else
		{
			day_night = "day";
		}

		if (day_night == "day")
		{
			lightingShader.SetVec3("lightColor", 0.5f, 1.0f, 0.31f);
		}
		else
		{
			lightingShader.SetVec3("lightColor", 0.08f, 0.24f, 0.75f);
		}
		lightPos.x = -3.0f;
	}
	else if (lightPos.x <= -3.0f)
	{
		ok = 0;
	}
	if (ok == 0)
	{
		lightPos.x += Fincrement;
	}
	else
	{
		lightPos.x -= Fincrement;
	}

	if (lightPos.x <= -1.0f)
	{
		lightPos.y += (Fincrement * 1.2);
		value = 0.6;
	}
	else if (lightPos.x <= -0.12f)
	{
		lightPos.y += (Fincrement * 0.5);
		value = 1;
	}
	else if (lightPos.x >= -0.12f && lightPos.x <= 0.12f)
	{

	}
	else if (lightPos.x >= -0.12f && lightPos.x < 1.0f)
	{
		lightPos.y -= (Fincrement * 0.5);
	}
	else
	{
		lightPos.y -= (Fincrement * 1.2);
		value = 0.6;
	}


	// Update the last color change time
	lastColorChangeTime1 = currentFrame;
}