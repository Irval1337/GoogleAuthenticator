using MessagingToolkit.QRCode.Codec;
using MessagingToolkit.QRCode.Codec.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace getQR { 
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
            this.FormBorderStyle = FormBorderStyle.None;
            TopMost = true;
            ShowInTaskbar = false;
            WindowState = FormWindowState.Normal;
            this.Bounds = new Rectangle(0, 0, Screen.AllScreens[Screen.AllScreens.Length - 1].Bounds.Right, Screen.AllScreens[Screen.AllScreens.Length - 1].Bounds.Bottom);
            BackgroundImage = Shoot();
        }

        private Bitmap Shoot() {
            var bmp = new Bitmap(ClientSize.Width, ClientSize.Height);
            using (var gr = Graphics.FromImage(bmp))
                gr.CopyFromScreen(0, 0, 0, 0, new Size(bmp.Width, bmp.Height));
            return bmp;
        }

        private Rectangle SelectedRectangle;

        private void SaveSelectedRectangle() {
            using (var bmp = new Bitmap(SelectedRectangle.Width, SelectedRectangle.Height))
            using (var gr = Graphics.FromImage(bmp)) {
                gr.DrawImage(BackgroundImage, -SelectedRectangle.Left, -SelectedRectangle.Top);
                try {
                    QRCodeDecoder decoder = new QRCodeDecoder();
                    string result = decoder.Decode(new QRCodeBitmapImage(bmp));
                    Clipboard.SetText(result);
                }
                catch {
                    Clipboard.SetText("NULL");
                }
                Application.Exit();
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e) {
            e.Graphics.DrawImageUnscaled(BackgroundImage, 0, 0);
            Pen pen = new Pen(Brushes.White, 1);
            pen.DashStyle = DashStyle.Custom;
            pen.DashPattern = new float[] { 3, 4 };
            e.Graphics.DrawRectangle(pen, SelectedRectangle);
            var r = new Region(ClientRectangle);
            r.Exclude(SelectedRectangle);
            using (var brush = new SolidBrush(Color.FromArgb(100, 0, 0, 0)))
                e.Graphics.FillRegion(brush, r);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Escape)
                Application.Exit();
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e) {
            SelectedRectangle.Location = e.Location;
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e) {
            var newSize = new Size(e.X - SelectedRectangle.Left, e.Y - SelectedRectangle.Top);
            if (MouseButtons == MouseButtons.Left)
                if (newSize.Width > 5 && newSize.Height > 5) {
                    SelectedRectangle.Size = newSize;
                    Invalidate();
                }
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e) {
            if (SelectedRectangle.Width > 0 && SelectedRectangle.Height > 0) {
                SaveSelectedRectangle();
                SelectedRectangle.Size = Size.Empty;
                Invalidate();
            }
        }

        protected override CreateParams CreateParams {
            get {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x80;
                return cp;
            }
        }
    }
}
