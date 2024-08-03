#include <random>
#include "WSerial.h"
#pragma once
#include <array>

namespace synthux {
  class Scale {
  public:
    Scale(): 
      _scale_index  { 0 },
      _trans_index  { 12 }
      {
        _PrepareScale();
      }
    
    uint8_t ScalesCount() {
      return _scales.size();
    }

    void SetScaleIndex(uint8_t index) {
      if (index != _scale_index) {
        _scale_index = index;
        _PrepareScale();
      }
    }

    float TransMult(const float value) {
      auto new_trans_index = static_cast<uint8_t>(value * (_trans.size() - 1));
      return _trans[new_trans_index];
    }

    float FreqAt(uint8_t idx) {
      return _scale[idx] * 0.5;
    }

    float Random() {
      std::uniform_int_distribution<uint8_t> note_distribution(0, _scale.size() - 1);
      return FreqAt(note_distribution(_rand_engine));
    }

  private:
      void _PrepareScale() {
        auto transposition = _trans[_trans_index];
        auto& scale = _scales[_scale_index];
        for (auto i = 0; i < scale.size(); i++) {
          _scale[i] = scale[i] * transposition;
        }
      }

      uint8_t _scale_index;
      uint8_t _trans_index;
      std::default_random_engine _rand_engine;

      static constexpr uint8_t kScaleSize = 8;

      std::array<float, kScaleSize> _scale;
      std::array<std::array<float, kScaleSize>, 3> _scales = {{
        { 130.81,	196.00,	233.08,	261.63,	293.66,	311.13,	349.23,	392.00 }, // Amara D3, A3, C4, D4, E4, F4, G4, A4, C5. | C3, G3, A#3, C4, D4, D#4, F4, G4
        { 130.81,	164.81,	174.61,	196.00,	220.00,	261.63,	329.63,	349.23 }, // Oxalis F3, A3, Bb3, C4, D4, F4, A4, Bb4, C5 | C3, E3, F3, G3, A3, C4, E4, F4
        { 130.81,	146.83,	155.56,	196.00,	233.08,	261.63,	293.66,	311.13 } // Pigmy F3, G3, Ab3, C4, Eb4, F4, G4, Ab4, C5 | C3, D3, D#3, G3, Bb3, C4, D4, D#4
      }};
      std::array<float, 25> _trans = { 
        0.5f, 
        0.52973154717962f, 
        0.56123102415466f,  0.594603557501335f, 
        0.629960524947413f, 0.667419927084995f, 
        0.707106781186527f, 0.749153538438323f, 
        0.793700525984085f, 0.840896415253703f, 
        0.890898718140331f, 0.943874312681689f, 
        1.f, 
        1.0594630943593f,   1.12246204830938f, 
        1.18920711500273f,  1.25992104989489f, 
        1.33483985417006f,  1.41421356237313f,
        1.49830707687673f,  1.58740105196826f, 
        1.6817928305075f,   1.78179743628076f, 
        1.88774862536348f, 
        2.f 
      };
  };
};




