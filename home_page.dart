import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:fl_chart/fl_chart.dart';
import 'info_card.dart';
import 'chart_page.dart';






/* =========================================================
   HOME PAGE – NUR AKTUELLE WERTE + BUTTON
   ========================================================= */
class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final DatabaseReference _rootRef =
      FirebaseDatabase.instanceFor(
        app: Firebase.app(),
        databaseURL:
            'https://aiit-2025-26-default-rtdb.europe-west1.firebasedatabase.app/',
      ).ref();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Wetterübersicht')),
      body: StreamBuilder<DatabaseEvent>(
        stream: _rootRef.onValue,
        builder: (context, snapshot) {
          if (!snapshot.hasData || snapshot.data!.snapshot.value == null) {
            return const Center(child: CircularProgressIndicator());
          }

          final data =
              snapshot.data!.snapshot.value as Map<dynamic, dynamic>;

          final temperatur = data['DHT11']?['temperatur'];
          final luftfeuchtigkeit = data['DHT11']?['luftfeuchtigkeit'];
          final niederschlag =
              data['sensorData']?['aktuellerZustand']?['Niederschlag'];

          List<FlSpot> tempSpots = [];
          List<FlSpot> humiditySpots = [];

          final history = data['history'];

          if (history is List) {
            int x = 1;
            for (final entry in history) {
              if (entry == null) continue;

              tempSpots.add(
                FlSpot(x.toDouble(),
                    (entry['temperatur'] as num).toDouble()),
              );
              humiditySpots.add(
                FlSpot(x.toDouble(),
                    (entry['luftfeuchtigkeit'] as num).toDouble()),
              );
              x++;
            }
          }

          return Padding(
            padding: const EdgeInsets.all(16),
            child: Column(
              children: [
                const Text('Aktueller Niederschlag',
                    style: TextStyle(fontSize: 18)),
                const SizedBox(height: 8),
                Text(
                  niederschlag ?? '–',
                  style: const TextStyle(
                      fontSize: 32, fontWeight: FontWeight.bold),
                ),

                const SizedBox(height: 32),

                InfoCard(
                  title: 'Temperatur',
                  value: temperatur != null ? '$temperatur °C' : '–',
                  icon: Icons.thermostat,
                ),
                const SizedBox(height: 16),
                InfoCard(
                  title: 'Luftfeuchtigkeit',
                  value: luftfeuchtigkeit != null
                      ? '$luftfeuchtigkeit %'
                      : '–',
                  icon: Icons.water_drop,
                ),

                

                // 🔥 BUTTON ZUR CHARTS PAGE
                const SizedBox(height: 24),

                SizedBox(
                  width: double.infinity, // 🔥 volle Breite
                  height: 56,             // 🔥 größere Höhe
                  child: ElevatedButton.icon(
                    icon: const Icon(Icons.show_chart, size: 24),
                    label: const Text(
                      'Messwert-Verlauf',
                      style: TextStyle(fontSize: 18),
                    ),
                    onPressed: () {
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                          builder: (_) => ChartsPage(
                            tempSpots: tempSpots,
                            humiditySpots: humiditySpots,
                          ),
                        ),
                      );
                    },
                  ),
                ),

              ],
            ),
          );
        },
      ),
    );
  }
}
