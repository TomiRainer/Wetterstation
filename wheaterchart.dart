import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';




/* =========================================================
   TEMPERATURE CHART
   ========================================================= */
class TemperatureChart extends StatelessWidget {
  final List<FlSpot> data;

  const TemperatureChart({super.key, required this.data});

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 260,
      child: LineChart(
        LineChartData(
          minX: 1,
          maxX: 5,
          minY: -10,
          maxY: 40,

          gridData: FlGridData(show: true),
          borderData: FlBorderData(show: true),

          titlesData: FlTitlesData(
            bottomTitles: AxisTitles(
              sideTitles: SideTitles(
                showTitles: true,
                interval: 1,
                getTitlesWidget: (value, _) =>
                    Text(value.toInt().toString()),
              ),
            ),
            leftTitles: AxisTitles(
              sideTitles: SideTitles(
                showTitles: true,
                interval: 10,
                getTitlesWidget: (value, _) =>
                    Text('${value.toInt()}°'),
              ),
            ),
            rightTitles: AxisTitles(sideTitles: SideTitles(showTitles: false)),
            topTitles: AxisTitles(sideTitles: SideTitles(showTitles: false)),
          ),

          lineBarsData: [
            LineChartBarData(
              spots: data,
              isCurved: true,
              color: Colors.red,
              barWidth: 3,
              dotData: FlDotData(show: true),
            ),
          ],
        ),
      ),
    );
  }
}


/* =========================================================
   HUMIDITY CHART
   ========================================================= */
class HumidityChart extends StatelessWidget {
  final List<FlSpot> data;

  const HumidityChart({super.key, required this.data});

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 260,
      child: LineChart(
        LineChartData(
          minX: 1,
          maxX: 5,
          minY: 0,
          maxY: 100,

          gridData: FlGridData(show: true),
          borderData: FlBorderData(show: true),

titlesData: FlTitlesData(
  bottomTitles: AxisTitles(
    sideTitles: SideTitles(
      showTitles: true,
      interval: 1,
      getTitlesWidget: (value, _) =>
          Text(value.toInt().toString()),
    ),
  ),

        leftTitles: AxisTitles(
          sideTitles: SideTitles(
            showTitles: true,
            interval: 20,
            getTitlesWidget: (value, meta) => SideTitleWidget(
              axisSide: meta.axisSide,
              space: 6,
              child: Transform.translate(
                offset: const Offset(-4, 0), // 👈 nach links
                child: SizedBox(
                  width: 32,
                  child: Text(
                    '${value.toInt()}%',
                    textAlign: TextAlign.right,
                    maxLines: 1,
                    softWrap: false,
                    style: const TextStyle(fontSize: 10),
                  ),
                ),
              ),
            ),
          ),
        ),

        rightTitles: AxisTitles(
          sideTitles: SideTitles(showTitles: false),
        ),
        topTitles: AxisTitles(
          sideTitles: SideTitles(showTitles: false),
        ),
      ),


          lineBarsData: [
            LineChartBarData(
              spots: data,
              isCurved: true,
              color: Colors.blue,
              barWidth: 3,
              dotData: FlDotData(show: true),
            ),
          ],
        ),
      ),
    );
  }
}
