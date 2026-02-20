import 'package:flutter/material.dart';
import 'wheaterchart.dart';
import 'package:fl_chart/fl_chart.dart';





/* =========================================================
   CHARTS PAGE – NUR DIAGRAMME
   ========================================================= */
class ChartsPage extends StatelessWidget {
  final List<FlSpot> tempSpots;
  final List<FlSpot> humiditySpots;

  const ChartsPage({
    super.key,
    required this.tempSpots,
    required this.humiditySpots,
  });

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Messwert-Verlauf')),
      body: SingleChildScrollView(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            const Text('🌡️ Temperatur-Verlauf (°C)',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
            const SizedBox(height: 16),
            TemperatureChart(data: tempSpots),

            const SizedBox(height: 32),

            const Text('💧 Luftfeuchtigkeit-Verlauf (%)',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
            const SizedBox(height: 16),
            HumidityChart(data: humiditySpots),
          ],
        ),
      ),
    );
  }
}