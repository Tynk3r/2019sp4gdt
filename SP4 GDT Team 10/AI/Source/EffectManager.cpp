#include "EffectManager.h"
#include "EffectBase.h"
#include "GL/glew.h"
#include "SceneBase.h"
#include "Application.h"
#include "EffectTrail.h"
#include "EffectHand.h"
#include "EffectReticle.h"
#include "EffectCloud.h"

void EffectManager::Init()
{
}

void EffectManager::Update(float dt)
{
	while (!effect_queue.empty()) 
	{
		effect_list.push_back(effect_queue.front());
		effect_queue.pop();
	}
	for (auto Effect : effect_list)
	{
		Effect->Update(dt);
	}
	while (!effect_queue.empty())//THIS IS INTENTIONAL
	{
		effect_list.push_back(effect_queue.front());
		effect_queue.pop();
	}
	std::vector<EffectBase*>::iterator it, end;
	it = effect_list.begin();
	end = effect_list.end();
	while (it != end)
	{
		if ((*it)->bIsDone)
		{
			// Delete if done
			delete *it;
			it = effect_list.erase(it);
			end = effect_list.end();
		}
		else
		{
			// Move on otherwise
			++it;
		}
	}
}

void EffectManager::Render(SceneBase * scene)
{
	float count = 0;
	for (auto Effect : effect_list)
	{
		count += 0.01f;
		scene->modelStack.PushMatrix();
		EffectTrail* EffTrail = dynamic_cast<EffectTrail*>(Effect);
		EffectHand* EffHand = dynamic_cast<EffectHand*>(Effect);
		EffectReticle* EffReticle = dynamic_cast<EffectReticle*>(Effect);
		if (EffTrail)
		{
			int i = 0;
			for (std::list<Vector3>::iterator it = EffTrail->trailPoints.begin(); it!=EffTrail->trailPoints.end(); ++it)
			{
				if (i >= EffTrail->iTotalPoints - 1) break;
				Vector3 pointA = *(it++);
				Vector3 pointB = *(it);
				it--;
				Vector3 AtoB = (pointB - pointA);
				if (AtoB.IsZero()) 
				{
					++i;
					continue;
				}
				float AtoB_Length = AtoB.Length();
				AtoB.Normalize();
				float lineWidth = Math::Max((float)i / (float)EffTrail->iTotalPoints,0.f);
				glLineWidth(lineWidth * EffTrail->fLineThickness);
				float angle_y = asin(AtoB.y);

				// Calculate the length of the laser when it is projected onto the x-z plane
				float theDirection_LengthInXYPlane = (float)(cos(angle_y));

				// Calculate the angle of the laser with respect from the x-axis (1st Quadrant)
				float angle_x = acos(AtoB.x / theDirection_LengthInXYPlane);

				// If the laser is going to the 3rd and 4th Quadrant, 
				// then we need to calculate the angle from x-axis in the clockwise direction
				if (AtoB.z >= 0)
					angle_x = (2 * Math::PI) - angle_x;

				// Calculate the angle of the laser from the z axis.
				float angle_z = acos(AtoB.z / theDirection_LengthInXYPlane);

				scene->modelStack.PushMatrix();
				scene->modelStack.Translate(pointA.x, pointA.y + 0.001f, pointA.z);
				scene->modelStack.Rotate(180 / Math::PI * angle_x, 0.0f, 1.0f, 0.0f);
			
				scene->modelStack.Rotate(180 / Math::PI * angle_y, 0.0f, 0.0f, 1.0f);
			
				scene->modelStack.Scale(AtoB_Length,1,1);
				rendermesh(scene, Effect);

				scene->modelStack.PopMatrix();
				++i;
			}
			glLineWidth(1.f);
		}
		else if (EffHand)
		{
			scene->modelStack.Translate(Effect->pos.x, Effect->pos.y, Effect->pos.z);
			if (!Effect->rotation.IsZero())
			{
				scene->modelStack.Rotate(Effect->rotation.x, 1, 0, 0);
				scene->modelStack.Rotate(Effect->rotation.y, 0, 1, 0);
				scene->modelStack.Rotate(Effect->rotation.z, 0, 0, 1);

			}
			scene->modelStack.Scale(Effect->scale.x, Effect->scale.y, Effect->scale.z);
			//glDepthFunc(GL_ALWAYS);
			rendermesh(scene, Effect);
			//glDepthFunc(GL_LESS);
		}
		else
		{
			scene->modelStack.Translate(Effect->pos.x, Effect->pos.y, Effect->pos.z);
			if (!Effect->rotation.IsZero())
			{
				scene->modelStack.Rotate(Effect->rotation.x, 1, 0, 0);
				scene->modelStack.Rotate(Effect->rotation.y, 0, 1, 0);
				scene->modelStack.Rotate(Effect->rotation.z, 0, 0, 1);

			}
			scene->modelStack.Scale(Effect->scale.x, Effect->scale.y, Effect->scale.z);
			if (EffReticle)
			{
				glLineWidth(EffReticle->reticleThickness);
				rendermesh(scene, Effect);
				glLineWidth(1);
			}
			else
				rendermesh(scene, Effect);
		}
		scene->modelStack.PopMatrix();
	}
	glUniform1f(scene->m_parameters[SceneBase::U_ALPHA], 1.f);
}

bool EffectManager::AddEffect(EffectBase* effect)
{
	//effect_list.push_back(effect);
	effect_queue.push(effect);
	return true;
}

void EffectManager::DoPrefabEffect(EFFECT_PREFABS prefab, Vector3 goPos)
{
	switch (prefab)
	{
	case PREFAB_PLACEOBJECT:
	{
		for (int i = 0; i < 8; ++i)
		{
			EffectCloud* newCloud = new EffectCloud(
				goPos + Vector3(Math::RandFloatMinMax(-0.5f, 0.5f), -0.5f + Math::RandFloatMinMax(0.f, 0.5f), Math::RandFloatMinMax(-0.5f, 0.5f)) * 0.5f
				, Math::RandFloatMinMax(0.25f, 0.75f)
				, Vector3(1, 1, 1) * Math::RandFloatMinMax(1.f, 3.f)
			);
			newCloud->vel += Vector3(0, 1, 0);
			this->AddEffect(newCloud);
		}
		break;
	}
	case PREFAB_PLACEVILLAGER:
	{
		for (int i = 0; i < 3; ++i)
		{
			EffectCloud* newCloud = new EffectCloud(
				goPos + Vector3(Math::RandFloatMinMax(-0.5f, 0.5f), 0, Math::RandFloatMinMax(-0.5f, 0.5f)) * 0.25f
				, Math::RandFloatMinMax(0.25f, 0.9f)
				, Vector3(1, 1, 1) * Math::RandFloatMinMax(0.8f, 1.5f)
			);
			this->AddEffect(newCloud);
		}
		break;
	}
	}
}

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{
	while (!effect_list.empty()) {
		delete effect_list.back();
		effect_list.pop_back();
	}
	while (!effect_queue.empty()) {
		delete effect_queue.front();
		effect_queue.pop();
	}
}

void EffectManager::rendermesh(SceneBase* scene,EffectBase* effect)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	if (scene->m_renderPass == SceneBase::RENDER_PASS_PRE)
	{
		Mtx44 lightDepthMVP = scene->m_lightDepthProj *
			scene->m_lightDepthView * scene->modelStack.Top();
		glUniformMatrix4fv(scene->m_parameters[SceneBase::U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &lightDepthMVP.a[0]);
		//effect->mesh->Render();
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (effect->mesh->textureArray[i] > 0)
			{
				glUniform1i(scene->m_parameters[SceneBase::U_SHADOW_COLOR_TEXTURE_ENABLED
					+ i], 1);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, effect->mesh->textureArray[i]);
				glUniform1i(scene->m_parameters[SceneBase::U_SHADOW_COLOR_TEXTURE + i], i);
			}
			else
				glUniform1i(scene->m_parameters[SceneBase::U_SHADOW_COLOR_TEXTURE_ENABLED
					+ i], 0);
		}
		effect->mesh->Render();
		return;
	}
	MVP = scene->projectionStack.Top() * scene->viewStack.Top() * scene->modelStack.Top();
	glUniformMatrix4fv(scene->m_parameters[SceneBase::U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = scene->viewStack.Top() * scene->modelStack.Top();
	glUniformMatrix4fv(scene->m_parameters[SceneBase::U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (effect->bLightEnabled)
	{
		glUniform1i(scene->m_parameters[SceneBase::U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(scene->m_parameters[SceneBase::U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		Mtx44 lightDepthMVP = scene->m_lightDepthProj *
			scene->m_lightDepthView * scene->modelStack.Top();
		glUniformMatrix4fv(scene->m_parameters[SceneBase::U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &lightDepthMVP.a[0]);

		//load material
		glUniform3fv(scene->m_parameters[SceneBase::U_MATERIAL_AMBIENT], 1, &effect->mesh->material.kAmbient.r);
		glUniform3fv(scene->m_parameters[SceneBase::U_MATERIAL_DIFFUSE], 1, &effect->mesh->material.kDiffuse.r);
		glUniform3fv(scene->m_parameters[SceneBase::U_MATERIAL_SPECULAR], 1, &effect->mesh->material.kSpecular.r);
		glUniform1f(scene->m_parameters[SceneBase::U_MATERIAL_SHININESS], effect->mesh->material.kShininess);
	}
	else
	{
		glUniform1i(scene->m_parameters[SceneBase::U_LIGHTENABLED], 0);
	}

	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (effect->mesh->textureArray[i] > 0)
		{
			glUniform1i(scene->m_parameters[SceneBase::U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, effect->mesh->textureArray[i]);
			glUniform1i(scene->m_parameters[SceneBase::U_COLOR_TEXTURE + i], i);
		}
		else
			glUniform1i(scene->m_parameters[SceneBase::U_COLOR_TEXTURE_ENABLED + i], 0);

	}
	glUniform1f(scene->m_parameters[SceneBase::U_ALPHA], effect->fAlpha);
	effect->mesh->Render();
	/*if (effect->mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}*/
}
