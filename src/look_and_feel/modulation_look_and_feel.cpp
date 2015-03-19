/* Copyright 2013-2015 Matt Tytel
 *
 * twytch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * twytch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with twytch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "modulation_look_and_feel.h"
#include "modulation_slider.h"
#include "mopo.h"

void ModulationLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
                                             float slider_pos, float min, float max,
                                             const Slider::SliderStyle style, Slider& slider) {
  ModulationSlider* mod_slider = dynamic_cast<ModulationSlider*>(&slider);
  if (!mod_slider)
    return;
  Slider* destination = mod_slider->getDestinationSlider();
  float destination_percentage = destination->valueToProportionOfLength(destination->getValue());
  float destination_range = destination->getMaximum() - destination->getMinimum();
  float mod_percentage = slider.getValue() / destination_range;

  if (mod_percentage == 0.0)
    g.fillAll(Colour(0x22ffaa00));
  else
    g.fillAll(Colour(0x55ffaa00));

  g.setColour(Colour(0x88ffbb99));

  if (style == Slider::SliderStyle::LinearBar) {
    float destination_position = width * destination_percentage;
    float mod_diff = width * mod_percentage;
    float from = std::min<float>(destination_position + mod_diff, destination_position);
    float to = std::max<float>(destination_position + mod_diff, destination_position);

    g.fillRect(x + from, float(y), to - from, float(height));
    g.setColour(Colour(0xbbffddaa));
    g.fillRect(x + destination_position + mod_diff, 1.0f * y, 2.0f, 1.0f * height);
  }
  else if (style == Slider::SliderStyle::LinearBarVertical) {
    float destination_position = height * (1.0f - destination_percentage);
    float mod_diff = height * mod_percentage;
    float from = std::min<float>(destination_position - mod_diff, destination_position);
    float to = std::max<float>(destination_position - mod_diff, destination_position);

    g.fillRect(float(x), y + from, float(width), to - from);
    g.setColour(Colour(0xbbffddaa));
    g.fillRect(1.0f * x, y + destination_position - mod_diff, 1.0f * width, 2.0f);
  }
}

void ModulationLookAndFeel::drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
                                                  float slider_pos, float min, float max,
                                                  const Slider::SliderStyle style, Slider& slider) {
}

void ModulationLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
                                             float slider_t, float start_angle, float end_angle,
                                             Slider& slider) {
  ModulationSlider* mod_slider = dynamic_cast<ModulationSlider*>(&slider);
  if (!mod_slider)
    return;

  Slider* destination = mod_slider->getDestinationSlider();
  float destination_percentage = destination->valueToProportionOfLength(destination->getValue());
  float destination_range = destination->getMaximum() - destination->getMinimum();
  float destination_angle = start_angle + destination_percentage * (end_angle - start_angle);
  float mod_diff = slider.getValue() * (end_angle - start_angle) / destination_range;

  float draw_radius = std::min(width / 2.0f, height / 2.0f);
  float knob_radius = 0.65f * draw_radius;
  PathStrokeType stroke_type =
      PathStrokeType(knob_radius, PathStrokeType::beveled, PathStrokeType::butt);

  if (mod_diff == 0.0)
    g.setColour(Colour(0x11ffaa44));
  else
    g.setColour(Colour(0x77ffaa00));
  g.fillEllipse(width / 2.0f - knob_radius, height / 2.0f - knob_radius,
                2.0 * knob_radius, 2.0 * knob_radius);

  Path active_section;
  float center_x = x + draw_radius;
  float center_y = y + draw_radius;
  if (destination_angle > mopo::PI)
    destination_angle -= 2.0 * mopo::PI;
  active_section.addCentredArc(center_x, center_y, knob_radius / 2.0, knob_radius / 2.0,
                               destination_angle, mod_diff, 0, true);

  g.setColour(Colour(0x88ffbb99));
  g.strokePath(active_section, stroke_type);

  float end_x = draw_radius + 0.9f * knob_radius * sin(destination_angle + mod_diff);
  float end_y = draw_radius - 0.9f * knob_radius * cos(destination_angle + mod_diff);
  g.setColour(Colour(0xffffddaa));
  g.drawLine(draw_radius, draw_radius, end_x, end_y, 1.0f);

  g.setColour(Colour(0xff000000));
  g.fillEllipse(draw_radius - knob_radius * 0.15f, draw_radius - knob_radius * 0.15f,
                2.0f * knob_radius * 0.15f, 2.0f * knob_radius * 0.15f);
}