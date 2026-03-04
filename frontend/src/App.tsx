import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom'
import Layout from './components/Layout'
import DistancePage from './pages/distance/DistancePage'
import ConvexHullPage from './pages/convex-hull/ConvexHullPage'

function ComingSoon({ name }: { name: string }) {
  return <p style={{ color: '#888' }}>{name} — coming soon.</p>
}

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Layout />}>
          <Route index element={<Navigate to="/algorithms/distance" replace />} />
          <Route path="algorithms/distance" element={<DistancePage />} />
          <Route path="algorithms/convex-hull" element={<ConvexHullPage />} />
          <Route path="algorithms/segment-intersection" element={<ComingSoon name="Line Segment Intersection" />} />
        </Route>
      </Routes>
    </BrowserRouter>
  )
}
