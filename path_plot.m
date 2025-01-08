function Path_plot(terrain, Path1, Path2, Path3)
  
  % Načtení dat
  terrain = load("terrain_new.dat");
  Path1 = load("AirplanePath.dat");
  Path2 = load("BoatPath.dat");
  Path3 = load("RoadPath.dat");
  
  width = 256;
  height = 256;

  %% První graf: Airplane Path
  figure();
  [x_coords, y_coords] = meshgrid(1:width, 1:height);
  terrain_plot = imshow(terrain, "displayrange", [-300, 1600], "colormap", jet);
  hold on;
  contour(terrain, 0:1, 'k');

  % Plot AirplanePath
  start = Path1(1, :);
  target = Path1(end, :);
  scatter([start(1), target(1)], [start(2), target(2)], 200, [1 0 0], '+');
  plot(Path1(:, 1), Path1(:, 2), 'r-', "linewidth", 2);

  xlabel('X');
  ylabel('Y');
  title('Airplane Path');
  colorbar();

  %% Druhý graf: Boat Path
  figure();
  terrain_plot = imshow(terrain, "displayrange", [-300, 1600], "colormap", jet);
  hold on;
  contour(terrain, 0:1, 'k');

  % Plot BoatPath
  start = Path2(1, :);
  target = Path2(end, :);
  scatter([start(1), target(1)], [start(2), target(2)], 200, [0 1 0], '+');
  plot(Path2(:, 1), Path2(:, 2), 'r-', "linewidth", 2);

  xlabel('X');
  ylabel('Y');
  title('Boat Path');
  colorbar();
   %% Třetí graf: Road Path
  figure();
  terrain_plot = imshow(terrain, "displayrange", [-300, 1600], "colormap", jet);
  hold on;
  contour(terrain, 0:1, 'k');

  % Plot BoatPath
  start = Path3(1, :);
  target = Path3(end, :);
  scatter([start(1), target(1)], [start(2), target(2)], 200, [0 1 0], '+');
  plot(Path3(:, 1), Path3(:, 2), 'r-', "linewidth", 2);

  xlabel('X');
  ylabel('Y');
  title('Road Path');
  colorbar();
end